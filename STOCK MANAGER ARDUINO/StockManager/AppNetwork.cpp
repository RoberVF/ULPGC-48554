#include "AppNetwork.h"
#include "Config.h"

AppWiFi network;

void AppWiFi::init() {
    WiFi.mode(WIFI_AP_STA);
    
    // Iniciamos el AP
    WiFi.softAP(AP_SSID, AP_PASS);
    Serial.print("[NET] AP Iniciado: ");
    Serial.println(AP_SSID);

    // Iniciamos la conexion al router
    Serial.print("[NET] Conectando a casa...");
    WiFi.begin(HOME_SSID, HOME_PASS);
}

void AppWiFi::update() {
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 10000) { // Comprobar cada 10s
        lastCheck = millis();
        if (WiFi.status() == WL_CONNECTED) {
            // Serial.println("WiFi OK"); // Solo para debug
        } else {
            Serial.println("[NET] WiFi down... reconectando");
            WiFi.reconnect();
        }
    }
}