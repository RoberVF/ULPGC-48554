#include "mBase.h"
#include "Config.h"
#include <LittleFS.h>

DataModel model;

/**
 * @brief Inicializa el modelo de datos y el sistema de archivos.
 * * Monta el sistema LittleFS. Si el archivo de base de datos no existe,
 * crea uno nuevo con un array JSON vacío para evitar errores de lectura.
 */
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

/**
 * @brief Carga la base de datos desde la memoria persistente.
 * * Lee el archivo database.json y lo deserializa en un documento JSON.
 * Si el archivo está corrupto, devuelve un array vacío.
 * * @return DynamicJsonDocument Documento con los datos cargados.
 */
DynamicJsonDocument DataModel::loadDatabase() {
    /// Reservamos memoria suficiente (ajusta 4096 según la cantidad de productos)
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

/**
 * @brief Guarda el estado actual de la base de datos en memoria.
 * * Serializa el documento JSON proporcionado y lo escribe en el sistema de archivos.
 * * @param doc Documento JSON con los datos actualizados a guardar.
 */
void DataModel::saveDatabase(JsonDocument& doc) {
    File file = LittleFS.open(DB_PATH, "w");
    if (file) {
        serializeJson(doc, file);
        file.close();
    }
}

/**
 * @brief Genera el siguiente ID único disponible (Simulación de AUTO_INCREMENT).
 * * Recorre todos los productos existentes para encontrar el ID más alto y le suma 1.
 * * @param array Array JSON de productos existentes.
 * @return int El nuevo ID generado.
 */
 int DataModel::generateNextId(JsonArray& array) {
    int maxId = 0;
    for (JsonVariant v : array) {
        int currentId = v["id"];
        if (currentId > maxId) maxId = currentId;
    }
    return maxId + 1;
}

/**
 * @brief Añade un nuevo producto a la base de datos.
 * * @param name Nombre del producto.
 * @param price Precio del producto.
 * @param stock Cantidad inicial de stock.
 * @return int El ID del producto recién creado, o -1 si el nombre está vacío.
 */
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

/**
 * @brief Obtiene todos los productos almacenados.
 * * @return String Cadena JSON con la lista completa de productos.
 */
String DataModel::findProducts() {
    // Simplemente leemos el archivo y lo devolvemos tal cual
    File file = LittleFS.open(DB_PATH, "r");
    if (!file) return "[]";
    String json = file.readString();
    file.close();
    return json;
}

/**
 * @brief Elimina un producto de la base de datos por su ID.
 * * @param id Identificador único del producto a eliminar.
 * @return true Si el producto fue encontrado y eliminado.
 * @return false Si no se encontró el ID.
 */
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

/**
 * @brief Busca productos que contengan un texto específico en su nombre.
 * * Realiza una búsqueda insensible a mayúsculas/minúsculas (LIKE %name%).
 * * @param name Texto a buscar en el nombre del producto.
 * @return String JSON Array con los productos que coinciden.
 */
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

/**
 * @brief Busca productos que coincidan exactamente con un nombre.
 * * @param name Nombre exacto del producto.
 * @return String JSON Array con los productos encontrados.
 */
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

/**
 * @brief Actualiza la información completa de un producto.
 * * @param id ID del producto a modificar.
 * @param name Nuevo nombre.
 * @param price Nuevo precio.
 * @param stock Nuevo stock.
 * @return true Si se realizó la actualización correctamente.
 * @return false Si no se encontró el producto.
 */
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

/**
 * @brief Incrementa el stock de un producto en una unidad.
 * * @param id ID del producto.
 * @return true Si se encontró el producto y se actualizó.
 * @return false Si no se encontró el producto.
 */
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

/**
 * @brief Decrementa el stock de un producto en una unidad.
 * * Solo decrementa si el stock actual es mayor que 0.
 * * @param id ID del producto.
 * @return true Si se encontró el producto (aunque no se haya restado por ser 0).
 * @return false Si no se encontró el producto.
 */
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

/**
 * @brief Elimina todos los datos de la base de datos.
 * * Sobrescribe el archivo de base de datos con un array vacío.
 * Útil para pruebas o reinicio de fábrica.
 */
void DataModel::cleanTable() {
    File file = LittleFS.open(DB_PATH, "w");
    file.print("[]");
    file.close();
    Serial.println("[MODEL] Tabla limpiada");
}