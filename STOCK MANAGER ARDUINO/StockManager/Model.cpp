#include "Model.h"
#include "Config.h"
#include <LittleFS.h>

DataModel model;

// Inicializa el sistema de archivos y crea la DB si no existe
void DataModel::init() {
    if (!LittleFS.begin(true)) {
        Serial.println("[MODEL] Error crítico: No se pudo montar LittleFS");
        return;
    }
    
    // Si no existe el archivo se crea vacio
    if (!LittleFS.exists(DB_PATH)) {
        cleanTable(); 
        Serial.println("[MODEL] Base de datos creada");
    } else {
        Serial.println("[MODEL] Base de datos cargada");
    }
}


DynamicJsonDocument DataModel::loadDatabase() {
    // Reservamos memoria suficiente (ajusta 4096 según la cantidad de productos)
    DynamicJsonDocument doc(4096); 
    File file = LittleFS.open(DB_PATH, "r");
    if (file) {
        DeserializationError error = deserializeJson(doc, file);
        if (error) {
            Serial.println("[MODEL] Error JSON corrupto, reiniciando DB");
            doc.to<JsonArray>();
        }
        file.close();
    } else {
        doc.to<JsonArray>();
    }
    return doc;
}

void DataModel::saveDatabase(JsonDocument& doc) {
    File file = LittleFS.open(DB_PATH, "w");
    if (file) {
        serializeJson(doc, file);
        file.close();
    }
}

// Simula el AUTO_INCREMENT de SQL buscando el ID más alto
int DataModel::generateNextId(JsonArray& array) {
    int maxId = 0;
    for (JsonVariant v : array) {
        int currentId = v["id"];
        if (currentId > maxId) maxId = currentId;
    }
    return maxId + 1;
}


int DataModel::addProduct(String name, float price, int stock) {
    if (name.isEmpty()) return -1;

    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();

    int newId = generateNextId(array);

    JsonObject newProduct = array.createNestedObject();
    newProduct["id"] = newId;
    newProduct["name"] = name;
    newProduct["price"] = price;
    newProduct["stock"] = stock;

    saveDatabase(doc);
    Serial.printf("[MODEL] Producto agregado: %s (ID: %d)\n", name.c_str(), newId);
    return newId;
}

String DataModel::findProducts() {
    // Simplemente leemos el archivo y lo devolvemos tal cual
    File file = LittleFS.open(DB_PATH, "r");
    if (!file) return "[]";
    String json = file.readString();
    file.close();
    return json;
}

bool DataModel::deleteProduct(int id) {
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();

    for (int i = 0; i < array.size(); i++) {
        if (array[i]["id"] == id) {
            array.remove(i);
            saveDatabase(doc);
            Serial.printf("[MODEL] Producto ID %d eliminado\n", id);
            return true;
        }
    }
    return false;
}

String DataModel::findProduct(String name) {
    // Busqueda tipo LIKE %name%
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();
    
    // Creamos un documento temporal solo con los resultados
    DynamicJsonDocument resultDoc(2048);
    JsonArray resultArray = resultDoc.to<JsonArray>();

    // Convertimos a minusculas para buscar sin distinguir mayusculas
    name.toLowerCase();

    for (JsonObject p : array) {
        String pName = p["name"].as<String>();
        pName.toLowerCase();
        
        if (pName.indexOf(name) >= 0) {
            resultArray.add(p);
        }
    }
    
    String output;
    serializeJson(resultArray, output);
    return output;
}

String DataModel::findProductByName(String name) {
    // Busqueda exacta
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();
    DynamicJsonDocument resultDoc(1024);
    JsonArray resultArray = resultDoc.to<JsonArray>();

    for (JsonObject p : array) {
        if (p["name"] == name) {
            resultArray.add(p);
        }
    }
    
    String output;
    serializeJson(resultArray, output);
    return output;
}

bool DataModel::updateProduct(int id, String name, float price, int stock) {
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();

    for (JsonObject p : array) {
        if (p["id"] == id) {
            p["name"] = name;
            p["price"] = price;
            p["stock"] = stock;
            saveDatabase(doc);
            return true;
        }
    }
    return false;
}

bool DataModel::increaseStock(int id) {
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();

    for (JsonObject p : array) {
        if (p["id"] == id) {
            int current = p["stock"];
            p["stock"] = current + 1;
            saveDatabase(doc);
            return true;
        }
    }
    return false;
}

bool DataModel::decreaseStock(int id) {
    DynamicJsonDocument doc = loadDatabase();
    JsonArray array = doc.as<JsonArray>();

    for (JsonObject p : array) {
        if (p["id"] == id) {
            int current = p["stock"];
            return true;
        }
    }
    return false;
}

void DataModel::cleanTable() {
    File file = LittleFS.open(DB_PATH, "w");
    file.print("[]");
    file.close();
    Serial.println("[MODEL] Tabla limpiada");
}