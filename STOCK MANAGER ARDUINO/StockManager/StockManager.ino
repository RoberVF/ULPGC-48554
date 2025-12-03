#include "Config.h"
#include "mBase.h"
#include "mSetup.h"
#include "AppNetwork.h"
#include "pBase.h"
#include "vLocalSetup.h"
#include "vLocalPrincipal.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

/**
 * @brief Configuración inicial del sistema (Boot).
 * * Secuencia de arranque:
 * 1. Iniciar puerto serie.
 * 2. Inicializar Modelos (Datos y Configuración).
 * 3. Inicializar Red (Usando configuración cargada).
 * 4. Inicializar Controlador (Servidor Web).
 */
void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Calibración táctil (Ajustar según tu pantalla CYD)
  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch(calData);

  model.init();
  setupModel.init();
  network.init();
  controller.init();

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
    // Si hay internet -> Mostramos el Dashboard
    vPrincipal.update();
  } else {
    // Si NO hay internet -> Mostramos el Setup (Teclado)
    vSetup.update();
  }
  delay(100);
}