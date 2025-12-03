#include "Config.h"
#include "mBase.h"
#include "mSetup.h"
#include "AppNetwork.h"
#include "pBase.h"
#include "vLocalSetup.h"
#include "vLocalPrincipal.h"
#include "TouchDrv.h"
#include <TFT_eSPI.h>

#define CYD_LED_PIN 21

TFT_eSPI tft = TFT_eSPI();

/**
 * @brief Configuración inicial del sistema (Boot).
 * Inicia todo lo que vamos a utilizar
 */
void setup() {
  Serial.begin(115200);

  pinMode(CYD_LED_PIN, OUTPUT);
  digitalWrite(CYD_LED_PIN, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  touch.init();

  model.init();
  setupModel.init();
  network.init();

  if (setupModel.getSSID() != "") {
    controller.init();
  } else {
    Serial.println("[MAIN] Modo Configuración: Servidor Web desactivado");
  }

  vSetup.init();
  vPrincipal.init();

  Serial.println("--- SISTEMA LISTO ---");
}

/**
 * @brief Bucle principal del sistema.
 * Mantiene viva la conexión de red y libera CPU.
 */
void loop() {
  network.update();
  if (WiFi.status() == WL_CONNECTED) {
    vPrincipal.update();  // Pantalla Azul (Dashboard)
  } else {
    vSetup.update();  // Pantalla Roja (Teclado)
  }
  delay(100);
}