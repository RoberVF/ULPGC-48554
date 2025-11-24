#include "Controller.h"
#include "Model.h"
#include "View.h"
#include <AsyncJson.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);
WebController controller;

void WebController::init() {
    
    // Mostrar HTML
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    // Obtener todos los productos
    server.on("/api/products", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = model.findProducts();
        request->send(200, "application/json", json);
    });

    // Meter productos
    AsyncCallbackJsonWebHandler *addHandler = new AsyncCallbackJsonWebHandler("/api/add", [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonObject jsonObj = json.as<JsonObject>();
        
        String name = jsonObj["name"];
        float price = jsonObj["price"] | 0.0; // Si no viene precio, ponemos 0, porseacaso
        int stock = jsonObj["stock"];

        if (name.isEmpty()) {
            request->send(400, "application/json", "{\"error\":\"Falta nombre\"}");
            return;
        }

        model.addProduct(name, price, stock);
        
        request->send(200, "application/json", "{\"status\":\"ok\", \"msg\":\"Producto anadido\"}");
    });
    server.addHandler(addHandler);

    // Borrar producto
    AsyncCallbackJsonWebHandler *deleteHandler = new AsyncCallbackJsonWebHandler("/api/delete", [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonObject jsonObj = json.as<JsonObject>();
        
        if (!jsonObj.containsKey("id")) {
             request->send(400, "application/json", "{\"error\":\"Falta ID\"}");
             return;
        }

        int id = jsonObj["id"];
        
        if (model.deleteProduct(id)) {
            request->send(200, "application/json", "{\"status\":\"ok\"}");
        } else {
            request->send(404, "application/json", "{\"error\":\"No encontrado\"}");
        }
    });
    server.addHandler(deleteHandler);

    // Actualizar stock, tanto incrementar como decrementar
    AsyncCallbackJsonWebHandler *updateStockHandler = new AsyncCallbackJsonWebHandler("/api/stock", [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonObject jsonObj = json.as<JsonObject>();
        int id = jsonObj["id"];
        String action = jsonObj["action"]; // "increase" o "decrease"

        bool success = false;
        if (action == "increase") {
            success = model.increaseStock(id);
        } else if (action == "decrease") {
            success = model.decreaseStock(id);
        }

        if (success) {
            request->send(200, "application/json", "{\"status\":\"ok\"}");
        } else {
            request->send(404, "application/json", "{\"error\":\"Error al actualizar\"}");
        }
    });

    // Actualizar producto entero
    AsyncCallbackJsonWebHandler *updateHandler = new AsyncCallbackJsonWebHandler("/api/update", [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonObject jsonObj = json.as<JsonObject>();
        
        if (!jsonObj.containsKey("id")) {
             request->send(400, "application/json", "{\"error\":\"Falta ID\"}");
             return;
        }

        int id = jsonObj["id"];
        String name = jsonObj["name"];
        float price = jsonObj["price"];
        int stock = jsonObj["stock"];
        
        if (model.updateProduct(id, name, price, stock)) {
            request->send(200, "application/json", "{\"status\":\"ok\"}");
        } else {
            request->send(404, "application/json", "{\"error\":\"No encontrado\"}");
        }
    });
    
    server.addHandler(updateHandler);
    server.addHandler(updateStockHandler);

    server.begin();
    Serial.println("[SERVER] Iniciado");
}