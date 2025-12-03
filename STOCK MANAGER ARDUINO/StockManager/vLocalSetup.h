#ifndef VLOCALSETUP_H
#define VLOCALSETUP_H

#include <TFT_eSPI.h>
#include "mSetup.h"

// Declaramos que existe un objeto 'tft' definido en otro lugar (StockManager.ino)
extern TFT_eSPI tft;

/**
 * @class LocalSetupView
 * @brief Vista local encargada de la configuración de credenciales Wi-Fi.
 * Muestra el estado de desconexión y proporciona un teclado virtual en pantalla
 * para introducir SSID y Contraseña.
 */
class LocalSetupView {
public:
    void init();
    void update();

private:
    // Estados internos de esta vista
    enum SetupState { STATE_ERROR, STATE_INPUT_SSID, STATE_INPUT_PASS };
    SetupState currentState = STATE_ERROR;

    bool isActive = false; // Para detectar si acabamos de entrar en esta vista
    bool needsRedraw = true;
    
    String inputText = "";
    String tempSSID = "";
    unsigned long lastTouchTime = 0;

    void drawErrorScreen();
    void drawKeyboard(String title, bool isPassword);
    void handleTouch(int x, int y);
    void handleKeyboardTouch(int x, int y);
};

extern LocalSetupView vSetup;

#endif