#include "vSetup.h"

/**
 * @var setup_html
 * @brief Página web SPA para introducir credenciales Wi-Fi.
 * Incluye estilos Tailwind CSS y lógica JS para enviar los datos vía API.
 */
const char setup_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Configuración WiFi</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-900 text-white font-sans flex items-center justify-center h-screen">
    <div class="w-full max-w-md bg-gray-800 p-8 rounded-lg shadow-lg">
        <h1 class="text-2xl font-bold mb-6 text-center text-blue-400">Configurar WiFi</h1>
        
        <div class="mb-4">
            <label class="block text-gray-300 text-sm font-bold mb-2">Nombre WiFi (SSID)</label>
            <input type="text" id="ssid" class="w-full p-2 rounded bg-gray-700 border border-gray-600 focus:outline-none focus:border-blue-500 text-white">
        </div>
        
        <div class="mb-6">
            <label class="block text-gray-300 text-sm font-bold mb-2">Contraseña</label>
            <input type="password" id="password" class="w-full p-2 rounded bg-gray-700 border border-gray-600 focus:outline-none focus:border-blue-500 text-white">
        </div>
        
        <button onclick="save()" class="w-full bg-blue-600 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded transition duration-200">
            Guardar y Conectar
        </button>
        
        <div id="status" class="mt-4 text-center text-sm text-gray-400"></div>
        
        <div class="mt-6 text-center">
            <a href="/" class="text-blue-400 hover:underline text-sm">← Volver a Stock Manager</a>
        </div>
    </div>

    <script>
        async function save() {
            const ssid = document.getElementById('ssid').value;
            const password = document.getElementById('password').value;
            const status = document.getElementById('status');

            if (!ssid) {
                status.innerText = "⚠️ El nombre de la red es obligatorio";
                status.classList.add("text-yellow-400");
                return;
            }

            status.innerText = "Guardando...";
            
            try {
                const res = await fetch('/api/setup', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({ ssid, password })
                });
                
                if (res.ok) {
                    status.innerText = "✅ Guardado. Reiniciando...";
                    status.classList.replace("text-gray-400", "text-green-400");
                    // Esperar un poco para que el usuario lea
                    setTimeout(() => location.reload(), 5000);
                } else {
                    status.innerText = "❌ Error al guardar";
                    status.classList.replace("text-gray-400", "text-red-400");
                }
            } catch (e) {
                status.innerText = "❌ Error de conexión";
                status.classList.replace("text-gray-400", "text-red-400");
            }
        }
    </script>
</body>
</html>
)rawliteral";