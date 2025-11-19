/*
* Este archivo se encarga de la conexion, tanto de crear el AP (con las credenciales de Config.h)
* como de conectar el ESP al wifi de casa.
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include "Config.h"

class AppWiFi {
public:
    void init() {
        WiFi.mode(WIFI_AP_STA); // Que sea modo AP y estacion
        
        // Aqui iniciamos el AP si fuera necesario
        WiFi.softAP(AP_SSID, AP_PASS);
        Serial.print("[NET] AP Iniciado: ");
        Serial.println(AP_SSID);

        // Conectamos el ESP con el router de mi casa para que tenga conexion a internet
        WiFi.begin("SSID_DEL_ROUTER_DE_MI_CASA", "PASS_DEL_ROUTER_DE_MI_CASA"); 
    }

    void update() {
        // Se actualiza la conexion por si se pierde la conexion que se vuelva a conectar
        static unsigned long lastCheck = 0;
        if (millis() - lastCheck > 5000) {
            lastCheck = millis();
            if (WiFi.status() == WL_CONNECTED) {
                Serial.print("[NET] Conectado. IP: ");
                Serial.println(WiFi.localIP());
            } else {
                Serial.println("[NET] Buscando WiFi...");
            }
        }
    }
};

AppWiFi network;

#endif