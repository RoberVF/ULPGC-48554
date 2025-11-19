/*
* Como lo estoy haciendo es que el modelo solo trabaja con los datos, no tiene idea de WiFi ni de HTML
*/

#ifndef MODEL_H
#define MODEL_H

#include <LittleFS.h>
#include <ArduinoJson.h>

class DataModel {
public:
    void init() {
        if (!LittleFS.begin(true)) {
            Serial.println("[MODEL] Error montando LittleFS");
            return;
        }
        Serial.println("[MODEL] Sistema de archivos OK");
        // Esto para que si no existe db la creamos vacia para evitar problemas
        if (!LittleFS.exists(DB_PATH)) {
            saveData("[]");
        }
    }

    String getData() {
        File file = LittleFS.open(DB_PATH, "r");
        if (!file) return "[]";
        String data = file.readString();
        file.close();
        return data;
    }

    void saveData(String json) {
        File file = LittleFS.open(DB_PATH, "w");
        if (file) {
            file.print(json);
            file.close();
            Serial.println("[MODEL] Datos guardados");
        }
    }

    // En un futuro, aqui meto el addProduct() el deleteProduct() y todos los metodos que necesite
};

DataModel model;

#endif