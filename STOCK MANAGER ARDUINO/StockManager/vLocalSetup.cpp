#include "vLocalSetup.h"
#include "TouchDrv.h" // <--- NUEVO INCLUDE

LocalSetupView vSetup;

const char* KB_ROW1 = "1234567890";
const char* KB_ROW2 = "QWERTYUIOP";
const char* KB_ROW3 = "ASDFGHJKL";
const char* KB_ROW4 = "ZXCVBNM";

void LocalSetupView::init() {
    currentState = STATE_ERROR;
}

void LocalSetupView::update() {
    if (!isActive) {
        isActive = true;
        needsRedraw = true;
        tft.fillScreen(TFT_BLACK); 
    }

    if (needsRedraw) {
        if (currentState == STATE_ERROR) drawErrorScreen();
        else if (currentState == STATE_INPUT_SSID) drawKeyboard("SSID:", false);
        else if (currentState == STATE_INPUT_PASS) drawKeyboard("PASS:", true);
        needsRedraw = false;
    }

    uint16_t x, y;
    // --- CAMBIO AQUÍ: Usamos 'touch' en vez de 'tft' ---
    if (touch.getTouch(&x, &y) && (millis() - lastTouchTime > 200)) {
        lastTouchTime = millis();
        handleTouch(x, y);
    }
}

void LocalSetupView::drawErrorScreen() {
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.drawCentreString("SIN CONEXION", 160, 60, 4);
    tft.setTextSize(2);
    tft.drawCentreString("Toca para configurar", 160, 110, 1);
    tft.fillRect(60, 160, 200, 50, TFT_WHITE);
    tft.setTextColor(TFT_RED);
    tft.drawCentreString("CONFIGURAR", 160, 175, 2);
}

void LocalSetupView::drawKeyboard(String title, bool isPassword) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.drawString(title, 5, 5, 2);
    tft.drawRect(5, 25, 310, 30, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    String show = isPassword ? "" : inputText;
    if (isPassword) for(int i=0; i<inputText.length(); i++) show += "*";
    tft.drawString(show, 10, 32, 2);

    int yStart = 65, w = 32, h = 30;
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    for(int i=0; i<10; i++) {
        tft.fillRect(i*w, yStart, w-2, h-2, TFT_WHITE);
        tft.drawChar(KB_ROW1[i], i*w + 8, yStart + 5, 2);
        tft.fillRect(i*w, yStart+h, w-2, h-2, TFT_WHITE);
        tft.drawChar(KB_ROW2[i], i*w + 8, yStart+h + 5, 2);
    }
    for(int i=0; i<9; i++) {
        tft.fillRect(i*w + 15, yStart+h*2, w-2, h-2, TFT_WHITE);
        tft.drawChar(KB_ROW3[i], i*w + 15 + 8, yStart+h*2 + 5, 2);
    }
    for(int i=0; i<7; i++) {
        tft.fillRect(i*w + 30, yStart+h*3, w-2, h-2, TFT_WHITE);
        tft.drawChar(KB_ROW4[i], i*w + 30 + 8, yStart+h*3 + 5, 2);
    }
    tft.fillRect(5, 200, 60, 35, TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("DEL", 15, 210, 2);
    tft.fillRect(245, 200, 70, 35, TFT_GREEN);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("OK", 265, 210, 2);
}

void LocalSetupView::handleTouch(int x, int y) {
    if (currentState == STATE_ERROR) {
        if (y > 150) { 
            currentState = STATE_INPUT_SSID;
            inputText = "";
            needsRedraw = true;
        }
        return;
    }
    handleKeyboardTouch(x, y);
}

void LocalSetupView::handleKeyboardTouch(int x, int y) {
    int row = (y - 65) / 30;
    int col = x / 32;
    char key = 0;
    if (row == 0 && col < 10) key = KB_ROW1[col];
    else if (row == 1 && col < 10) key = KB_ROW2[col];
    else if (row == 2) { int c = (x-15)/32; if(c>=0 && c<9) key = KB_ROW3[c]; }
    else if (row == 3) { int c = (x-30)/32; if(c>=0 && c<7) key = KB_ROW4[c]; }

    if (y > 200) { 
        if (x < 70) { 
            if (inputText.length() > 0) inputText.remove(inputText.length()-1);
        } else if (x > 245) { 
            if (currentState == STATE_INPUT_SSID) {
                tempSSID = inputText;
                inputText = "";
                currentState = STATE_INPUT_PASS;
            } else {
                setupModel.saveCredentials(tempSSID, inputText);
                tft.fillScreen(TFT_BLACK);
                tft.setTextColor(TFT_GREEN);
                tft.drawCentreString("GUARDADO", 160, 100, 4);
                delay(1000);
                ESP.restart();
            }
        }
        needsRedraw = true;
    } else if (key != 0) {
        inputText += key;
        needsRedraw = true;
    }
}