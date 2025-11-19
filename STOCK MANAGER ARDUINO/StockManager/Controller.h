#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ESPAsyncWebServer.h>
#include "Model.h"
#include "View.h"

AsyncWebServer server(80);

class WebController {
public:
    void init() {
        // Ruta principal (/), muestra el html de View.h
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send_P(200, "text/html", index_html);
            Serial.println("[SERVER] Cliente en Home");
        });

        // Obtenemos los productos llamando al modelo
        server.on("/api/products", HTTP_GET, [](AsyncWebServerRequest *request){
            String json = model.getData();
            request->send(200, "application/json", json);
        });

        // Metemos productos, tambien llamando al modelo
        server.on("/api/add", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, 
            [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
              // De momento no funciona porque no tengo los metodos de add, delete, etc hechos en el modelo
                Serial.println("[SERVER] Peticion de incluir recibida");
                request->send(200, "application/json", "{\"status\":\"ok\"}");
        });

        server.begin();
        Serial.println("[SERVER] Servidor HTTP iniciado");
    }
};

WebController controller;

#endif