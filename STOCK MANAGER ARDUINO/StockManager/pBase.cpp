#include "pBase.h"
#include "mBase.h"
#include "mSetup.h"
#include "vPrincipal.h"
#include "vSetup.h"
#include <AsyncJson.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);
WebController controller;

/**
 * @brief Inicializa el servidor web y define los endpoints de la API.
 * * Configura las rutas para servir la interfaz web (HTML) y para manejar
 * las peticiones AJAX (API REST) que interactúan con el modelo de datos.
 * Inicia el servidor en el puerto 80.
 */
void WebController::init() {

  /**
     * @brief Ruta Raíz (GET /).
     * Sirve el archivo HTML principal de la aplicación.
     */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  /**
     * @brief GET /setup
     * Sirve la página de configuración Wi-Fi.
     */
  server.on("/setup", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", setup_html);
  });

  /**
     * @brief API: Obtener Productos (GET /api/products).
     * Devuelve la lista completa de productos en formato JSON.
     */
  server.on("/api/products", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = model.findProducts();
    request->send(200, "application/json", json);
  });

  /**
     * @brief API: Añadir Producto (POST /api/add).
     * Recibe un JSON con {name, price, stock} y crea un nuevo registro.
     */
  AsyncCallbackJsonWebHandler *addHandler = new AsyncCallbackJsonWebHandler("/api/add", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject jsonObj = json.as<JsonObject>();

    String name = jsonObj["name"];
    float price = jsonObj["price"] | 0.0;  // Si no viene precio, ponemos 0, porseacaso
    int stock = jsonObj["stock"];

    if (name.isEmpty()) {
      request->send(400, "application/json", "{\"error\":\"Falta nombre\"}");
      return;
    }

    model.addProduct(name, price, stock);

    request->send(200, "application/json", "{\"status\":\"ok\", \"msg\":\"Producto anadido\"}");
  });
  server.addHandler(addHandler);

  /**
     * @brief API: Eliminar Producto (POST /api/delete).
     * Recibe un JSON con {id} y elimina el producto correspondiente.
     */
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

  /**
     * @brief API: Modificar Stock (POST /api/stock).
     * Recibe un JSON con {id, action} donde action puede ser "increase" o "decrease".
     */
  AsyncCallbackJsonWebHandler *updateStockHandler = new AsyncCallbackJsonWebHandler("/api/stock", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject jsonObj = json.as<JsonObject>();
    int id = jsonObj["id"];
    String action = jsonObj["action"];  // "increase" o "decrease"

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

  /**
     * @brief API: Actualizar Producto (POST /api/update).
     * Recibe un JSON con {id, name, price, stock} y actualiza todos los campos.
     */
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

  /**
     * @brief POST /api/setup
     * Recibe nuevas credenciales Wi-Fi, las guarda y reinicia el ESP32.
     * * @param ssid Nombre de la red.
     * @param password Contraseña de la red.
     */
  AsyncCallbackJsonWebHandler *setupHandler = new AsyncCallbackJsonWebHandler("/api/setup", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject jsonObj = json.as<JsonObject>();

    String ssid = jsonObj["ssid"];
    String password = jsonObj["password"];

    if (ssid.isEmpty()) {
      request->send(400, "application/json", "{\"error\":\"Falta SSID\"}");
      return;
    }

    // Guardar en memoria permanente
    setupModel.saveCredentials(ssid, password);

    request->send(200, "application/json", "{\"status\":\"ok\", \"msg\":\"Guardado. Reiniciando...\"}");

    // Reiniciar ESP32 para aplicar cambios (damos 1s para que llegue la respuesta al navegador)
    delay(1000);
    ESP.restart();
  });

  server.addHandler(setupHandler);
  server.addHandler(updateHandler);
  server.addHandler(updateStockHandler);

  server.begin();
  Serial.println("[SERVER] Iniciado");
}