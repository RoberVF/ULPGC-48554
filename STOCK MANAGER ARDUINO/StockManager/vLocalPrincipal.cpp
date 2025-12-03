#include "vLocalPrincipal.h"
#include "TouchDrv.h"

LocalPrincipalView vPrincipal;

void LocalPrincipalView::init() {
    currentIndex = 0;
}

void LocalPrincipalView::update() {
    // Al entrar en esta vista (transición desde Setup)
    if (!isActive) {
        isActive = true;
        loadData(); // Cargar datos frescos de la BD
        tft.fillScreen(TFT_BLACK);
        needsRedraw = true;
    }

    // Refrescar cada cierto tiempo (opcional) o si cambia algo
    if (needsRedraw) {
        drawDashboard();
        needsRedraw = false;
    }

    // Táctil
    uint16_t x, y;
    if (touch.getTouch(&x, &y) && (millis() - lastTouchTime > 250)) {
        lastTouchTime = millis();
        handleTouch(x, y);
    }
}

void LocalPrincipalView::loadData() {
    String json = model.findProducts();
    DeserializationError error = deserializeJson(currentData, json);
    if (!error) {
        JsonArray array = currentData.as<JsonArray>();
        totalProducts = array.size();
        if (currentIndex >= totalProducts) currentIndex = 0;
    }
}

void LocalPrincipalView::drawDashboard() {
    // Header Azul
    tft.fillRect(0, 0, 320, 30, TFT_BLUE);
    tft.setTextColor(TFT_WHITE, TFT_BLUE);
    tft.setTextSize(2);
    tft.drawString("STOCK MANAGER", 10, 5);
    tft.fillCircle(300, 15, 6, TFT_GREEN); // Led Online

    JsonArray array = currentData.as<JsonArray>();
    
    // Fondo negro para limpiar el área de contenido
    tft.fillRect(0, 31, 320, 150, TFT_BLACK);

    if (totalProducts == 0) {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawCentreString("Sin Productos", 160, 100, 4);
        return;
    }

    JsonObject p = array[currentIndex];
    String name = p["name"].as<String>();
    float price = p["price"];
    int stock = p["stock"];

    // Datos del Producto
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawCentreString(name, 160, 50, 4); // Nombre Grande

    tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    tft.setTextSize(2);
    tft.drawCentreString(String(price) + " EUR", 160, 90, 1);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("Stock: " + String(stock), 160, 120, 4);

    // Botones
    // Prev (<)
    tft.fillRect(5, 190, 60, 45, TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("<", 25, 200, 2);

    // Menos (-)
    tft.fillRect(70, 190, 80, 45, TFT_RED);
    tft.drawString("-", 105, 200, 4);

    // Mas (+)
    tft.fillRect(155, 190, 80, 45, TFT_GREEN);
    tft.drawString("+", 190, 200, 4);

    // Next (>)
    tft.fillRect(240, 190, 75, 45, TFT_DARKGREY);
    tft.drawString(">", 270, 200, 2);
}

void LocalPrincipalView::handleTouch(int x, int y) {
    if (totalProducts == 0) {
        loadData(); // Intentar recargar
        needsRedraw = true;
        return;
    }

    JsonArray array = currentData.as<JsonArray>();
    int id = array[currentIndex]["id"];

    if (y > 180) { // Zona Botones
        if (x < 65) { // Prev
            currentIndex--;
            if (currentIndex < 0) currentIndex = totalProducts - 1;
        } 
        else if (x < 150) { // Menos
            model.decreaseStock(id);
            loadData(); // Recargar dato actualizado
        }
        else if (x < 235) { // Mas
            model.increaseStock(id);
            loadData();
        }
        else { // Next
            currentIndex++;
            if (currentIndex >= totalProducts) currentIndex = 0;
        }
        needsRedraw = true;
    }
}