#include "AppNetwork.h"
#include "Config.h"
#include "mSetup.h"

AppWiFi network;

/**
 * @brief Inicializa la red Wi-Fi usando credenciales persistentes.
 * * 1. Configura modo AP + Station.
 * 2. Inicia el AP "StockManager-AP" (siempre disponible).
 * 3. Consulta 'setupModel' para ver si hay credenciales guardadas.
 * - Si las hay: Intenta conectar a esa red.
 * - Si no las hay: Intenta conectar a la red hardcoded en Config.h (fallback).
 */
void AppWiFi::init()
{
    WiFi.mode(WIFI_STA);

    // Intentamos cargar credenciales guardadas
    String savedSSID = setupModel.getSSID();
    String savedPass = setupModel.getPassword();

    if (savedSSID != "") {
        Serial.print("[NET] Conectando a credenciales guardadas: ");
        Serial.println(savedSSID);
        WiFi.begin(savedSSID.c_str(), savedPass.c_str());
    } else {
        // CAMBIO: Si no hay nada guardado, usamos OBLIGATORIAMENTE las de Config.h
        Serial.print("[NET] Conectando a Config.h: ");
        Serial.println(HOME_SSID);
        WiFi.begin(HOME_SSID, HOME_PASS);
    }
    
    // Esperamos un poco para ver si conecta y mostrar la IP
    Serial.print("Conectando");
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 10) {
        delay(500);
        Serial.print(".");
        retries++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n[NET] ¡Conectado!");
        Serial.print("[NET] IP para acceder: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n[NET] Fallo al conectar. Reintentando en segundo plano...");
    }
}

/**
 * @brief Supervisa la conexión y reconecta si es necesario.
 * * Solo intenta reconectar si previamente se había configurado un SSID
 * (ya sea en memoria o en Config.h). Evita reconexiones ciegas si no hay red configurada.
 */
void AppWiFi::update()
{
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 10000)
    { // Comprobar cada 10s
        lastCheck = millis();
        // Solo intentamos reconectar si tenemos un SSID configurado
        if (WiFi.status() != WL_CONNECTED && (setupModel.getSSID() != "" || String(HOME_SSID) != ""))
        {
            Serial.println("[NET] WiFi caído... reconectando");
            WiFi.reconnect();
        }
    }
}