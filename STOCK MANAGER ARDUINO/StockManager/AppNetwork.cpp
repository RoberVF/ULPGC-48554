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
void AppWiFi::init() {
  WiFi.mode(WIFI_STA);

  // Intentamos cargar credenciales guardadas
  String savedSSID = setupModel.getSSID();
  String savedPass = setupModel.getPassword();

  if (savedSSID != "") {
    Serial.print("[NET] Conectando a credenciales guardadas: ");
    Serial.println(savedSSID);
    WiFi.begin(savedSSID.c_str(), savedPass.c_str());
  } else {
    Serial.println("[NET] No hay credenciales guardadas.");
    Serial.println("[NET] Esperando configuración desde la pantalla táctil...");
  }
}

/**
 * @brief Supervisa la conexión y reconecta si es necesario.
 * * Solo intenta reconectar si previamente se había configurado un SSID
 * (ya sea en memoria o en Config.h). Evita reconexiones ciegas si no hay red configurada.
 */
void AppWiFi::update() {
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {  // Comprobar cada 10s
    lastCheck = millis();
    // Solo intentamos reconectar automáticamente SI ya tenemos credenciales guardadas.
    // Si no las tenemos, es absurdo intentar reconectar (no sabemos a dónde).
    String savedSSID = setupModel.getSSID();

    if (savedSSID != "" && WiFi.status() != WL_CONNECTED) {
      Serial.println("[NET] Conexión perdida... reintentando conectar");
      WiFi.reconnect();
    }
  }
}