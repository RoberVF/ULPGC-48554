#include "mSetup.h"

SetupModel setupModel;

/**
 * @brief Inicializa el modelo.
 * Actualmente no requiere acciones específicas al inicio, pero se mantiene
 * por consistencia con la arquitectura del sistema.
 */
void SetupModel::init() {
    // No hace falta iniciar nada especifico aqui para Preferences, 
    // pero lo dejamos por consistencia con el patron.
}

/**
 * @brief Guarda las credenciales en el espacio de nombres 'wifi_config'.
 * Abre el espacio en modo lectura/escritura (false), guarda los valores y cierra.
 * * @param ssid SSID de la red a guardar.
 * @param password Contraseña de la red a guardar.
 */
void SetupModel::saveCredentials(String ssid, String password) {
    preferences.begin("wifi_config", false); // "wifi_config" es el nombre del espacio de nombres
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();
    Serial.println("[SETUP] Credenciales guardadas");
}

/**
 * @brief Lee el SSID desde la memoria flash.
 * Abre el espacio en modo solo lectura (true) para mayor seguridad.
 * * @return String El SSID almacenado.
 */
String SetupModel::getSSID() {
    preferences.begin("wifi_config", true); // true = modo solo lectura
    String ssid = preferences.getString("ssid", "");
    preferences.end();
    return ssid;
}

/**
 * @brief Lee la contraseña desde la memoria flash.
 * Abre el espacio en modo solo lectura (true).
 * * @return String La contraseña almacenada.
 */
String SetupModel::getPassword() {
    preferences.begin("wifi_config", true);
    String password = preferences.getString("password", "");
    preferences.end();
    return password;
}

/**
 * @brief Elimina completamente el espacio de nombres 'wifi_config'.
 * Esto borra SSID, contraseña y cualquier otra clave guardada bajo este namespace.
 */
void SetupModel::clearCredentials() {
    preferences.begin("wifi_config", false);
    preferences.clear();
    preferences.end();
    Serial.println("[SETUP] Credenciales borradas");
}