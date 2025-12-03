#ifndef MSETUP_H
#define MSETUP_H

#include <Arduino.h>
#include <Preferences.h>

/**
 * @class SetupModel
 * @brief Gestiona el almacenamiento persistente de la configuración Wi-Fi.
 * * Utiliza la librería 'Preferences' del ESP32 para guardar el SSID y la contraseña
 * en la memoria flash no volátil (NVS), de modo que sobrevivan a reinicios y apagados.
 */
class SetupModel {
public:
  /**
     * @brief Inicializa el modelo de configuración.
     */
  void init();

  /**
     * @brief Guarda las credenciales Wi-Fi en memoria permanente.
     * @param ssid Nombre de la red Wi-Fi.
     * @param password Contraseña de la red.
     */
  void saveCredentials(String ssid, String password);

  /**
     * @brief Recupera el SSID almacenado.
     * @return String El SSID guardado o una cadena vacía si no existe.
     */
  String getSSID();

  /**
     * @brief Recupera la contraseña almacenada.
     * @return String La contraseña guardada o una cadena vacía si no existe.
     */
  String getPassword();

  /**
     * @brief Borra todas las credenciales almacenadas (Reset de fábrica).
     * Útil para limpiar la configuración y volver al estado inicial.
     */
  void clearCredentials();

private:
  /** @brief Instancia de Preferences para acceso a la NVS. */
  Preferences preferences;
};

/** @brief Instancia global del modelo de configuración. */
extern SetupModel setupModel;

#endif