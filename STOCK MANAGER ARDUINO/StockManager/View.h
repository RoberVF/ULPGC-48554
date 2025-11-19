/*
* Aqui meto el HTML de la vista
*/

#ifndef VIEW_H
#define VIEW_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Stock Manager MVP</title>
    <style>
        body { font-family: sans-serif; padding: 20px; text-align: center; }
        button { padding: 10px 20px; font-size: 16px; margin: 10px; cursor: pointer; }
    </style>
</head>
<body>
    <h1>📦 Stock Manager (Modo Texto)</h1>
    <p>Sistema funcionando en ESP32</p>
    <div id="status">Conectado</div>
    </body>
</html>
)rawliteral";

#endif