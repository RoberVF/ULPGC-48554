#include "Config.h"
#include "Model.h"
#include "AppNetwork.h"
#include "Controller.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- INICIANDO STOCK MANAGER ---");

    model.init();
    network.init();
    controller.init();

    Serial.println("--- SISTEMA LISTO ---");
}

void loop() {
    network.update();
    delay(100);
}