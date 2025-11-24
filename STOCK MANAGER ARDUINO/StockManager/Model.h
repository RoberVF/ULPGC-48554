#ifndef MODEL_H
#define MODEL_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DataModel {
public:
    void init();
    
    int addProduct(String name, float price, int stock);

    String findProducts();

    bool deleteProduct(int id);

    String findProduct(String name);

    String findProductByName(String name);

    bool updateProduct(int id, String name, float price, int stock);

    bool increaseStock(int id);
    bool decreaseStock(int id);

    void cleanTable(); // Solo para testing

private:
    // Helpers internos para no repetir código
    DynamicJsonDocument loadDatabase();
    void saveDatabase(JsonDocument& doc);
    int generateNextId(JsonArray& array);
};

extern DataModel model;

#endif