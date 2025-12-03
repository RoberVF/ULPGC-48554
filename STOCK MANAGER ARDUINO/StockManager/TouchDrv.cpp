#include "TouchDrv.h"

SPIClass mySpi(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TouchDriver touch;

void TouchDriver::init() {
    // Iniciar el SPI secundario solo para el táctil
    mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    ts.begin(mySpi);
    ts.setRotation(1); // Mismo que la pantalla
}

bool TouchDriver::getTouch(uint16_t *x, uint16_t *y) {
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        
        // Calibración manual para CYD (Mapeo de 0-4096 a 0-320/240)
        // Invertimos y mapeamos según la rotación 1
        *x = map(p.x, 200, 3700, 0, 320); 
        *y = map(p.y, 240, 3800, 0, 240);
        
        return true;
    }
    return false;
}