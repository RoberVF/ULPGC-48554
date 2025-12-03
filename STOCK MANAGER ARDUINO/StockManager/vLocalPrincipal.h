#ifndef VLOCALPRINCIPAL_H
#define VLOCALPRINCIPAL_H

#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "mBase.h"

extern TFT_eSPI tft;

/**
 * @class LocalPrincipalView
 * @brief Vista principal (Dashboard) para la gestión de stock.
 * Muestra el producto actual, su precio y stock, y permite modificar la cantidad
 * o navegar entre productos mediante botones táctiles.
 */
class LocalPrincipalView {
public:
    void init();
    
    /**
     * @brief Actualiza la vista principal.
     * Si detecta que el sistema acaba de conectarse, carga los datos.
     */
    void update();

private:
    bool isActive = false;
    bool needsRedraw = true;
    unsigned long lastTouchTime = 0;

    // Datos locales
    JsonDocument currentData;
    int currentIndex = 0;
    int totalProducts = 0;

    void loadData();
    void drawDashboard();
    void handleTouch(int x, int y);
};

extern LocalPrincipalView vPrincipal;

#endif