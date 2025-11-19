#include "Config.h"
#include "Model.h"
#include "AppNetwork.h"
#include "Controller.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("--- INICIANDO STOCK MANAGER MVP ---");

    // Iniciamos el modelo
    model.init();

    // Iniciamos la red (lo conectamos al wifi y creamos el AP)
    network.init();

    // Iniciamos el controlador
    controller.init();

    Serial.println("--- SISTEMA LISTO ---");
}

void loop() {
    network.update(); // Para si se desconecta de la WiFi

    delay(100); 
}