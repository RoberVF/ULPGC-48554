# SPRINT 7. MIGRACION DEL PROYECTO A ARDUINO, ESP, WEB {#sprint7_page}
Teniendo en cuenta la idea principal de desarrollar la aplicacion real, vamos a desglosar como seria el procedimiento:
- El ESP como "servidor" y como "Access Point" ya que nuestro telefono se conectara a el.
- El telefono movil se conectara a la red WiFi del ESP.
- En cuanto a la Web App, una vez que el telefono este conectado a la red WiFi del ESP, se abrira el navegador del telefono y se accedera a la direccion IP del ESP. Ahi encontraremos la vista, desarrollada solamente en HTML, CSS y JS.
- Se debera de reescribir todo el proyecto a C++, ya que el ESP no tiene capacidad de interpretacion de PHP y, por tanto, habra que utilizar la misma logica que tenemos de la aplicacion PHP a C++, montar el enrutamiento, modelo, controlador, todo en C++.
- Una vez esto es hecho, cuando se realice un cambio en la Web App desde el dispositivo movil, se hara un fetch a una ruta de las desarrolladas en C++, consiguiendo asi la modificacion que queramos. Basicamente hacer una API REST en C++ que este en el ESP.
- Ademas, el ESP tiene su pantalla TFT la cual muestra otra informacion, en este caso, la lista de productos y el aumento/decremento de stock.
- Lo mas importante es que tanto la Web App como la pantalla TFT del ESP deben trabajar sobre la misma base de datos y el ESP no tiene una forma nativa de utilizar SQLite. Para ello trabajaremos sobre un archivo .json que guardaremos en la memoria SPIFFS del ESP. Ambos (la Web App y el ESP) escribiran sobre dicho archivo, manteniendo asi el modelo unificado.

### El ESP
Se debera de programar en C++/Arduino y se deberan de hacer las siguientes cosas:
- El Access Point WiFi (Utilizando la libreria proporcionada por el profesor, ya que es mejor que la basica WiFi.h)
- El servidor web (Utilizando a priori la libreria WebServer.h)
- El controlador de la pantalla TFT (He encontrado la libreria TFT_eSPI.h, ahora habra que ver que sea valida)
- El "Modelo" / Gestor de datos, entendiendo como esta la API o el "backend" en C++, convirtiendo el ProductController.php en una API REST. Aqui se definiran rutas tipo /api/products [GET], /api/add [POST], /api/stock/increase [POST], etc.

## La Web App
Ahora no tendremos una aplicacion "fullstack" sino un SPA (Single Page Application) que sera solamente frontend. Como el ESP guardara y manejara las funcionalidades, cuando el usuario con su telefono este conectado al WiFi del ESP y acceda a la direccion IP de este, se enviaran los tres archivos (HTML, CSS y JS).
A partir de ahi, sera el JS el encargado de fetchear las rutas, es decir, si necesito por ejemplo, agregar algun producto manualmente, hara un fetch a /api/add para meterlo o cuando se necesite la lista de productos, estos se conseguiran haciendo una peticion a la API del ESP.

### La Base de Datos
Como comentaba al principio, no se podra utilizar SQLite de forma nativa y sencilla en el ESP. La solucion que he encontrado ha sido utilizar la persistencia que ofrece el ESP con su sistema de archivos internos SPIFFS o LittleFS (Como aun no he hecho la aplicacion no se mucho acerca de esto).
Suponiendo que esto del SPIFFS funcione, en lugar de una base de datos SQL, la "base de datos" sera directamente un archivo .json, por ejemplo, database.json que guardare en la memoria SPIFFS del ESP.
Tanto la Web App como la "aplicacion" de la pantalla TFT escribiran sobre el mismo archivo database.json, consiguiendo mantener asi el modelo unificado.

### La pantalla TFT
Cuando el ESP arranque, leera el archivo database.json y mostrara los productos en la TFT. Si se pulsa un boton fisico en la pantalla, por ejemplo "STOCK +", se incrementara el stock del producto y se refrescara la pantalla.
Si alguien incluye algun producto desde la Web App del telefono, programaremos el ESP para que se refresque la TFT. Aunque de momento, incluiremos un boton de refrescar en la pantalla para actualizar la informacion de la base de datos.
Dado que no podemos integrar un HTML + CSS en el ESP, debo crear la interfaz grafica a mano. Para ello, utilizare la libreria TFT_eSPI.h, la cual no he utilizado nunca pero por lo que he estado leyendo es la mas comun cuando se trata de hacer interfaces graficas en TFT y la mas potente.