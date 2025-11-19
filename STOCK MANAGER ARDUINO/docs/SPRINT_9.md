# SPRINT 9
Después de todos los problemas que tuve en el SPRINT_8 configurando la placa y, por petición del profesor, he comenzado primero en escribir el código, basandome en MVC y sectorizando los datos lo más posible. Así he conseguido que el programa compile, después de un par de errores, y, aunque sin probarlo en la placa aún, tener un resultado con mucho mayor potencial que el visto en el SPRINT anterior. Hablando un poco de todos los archivos:

### Config.h
Este es el típico archivo que suelo utilizar en node.js para la configuración de las variables de entorno para llamar del .env al código directamente. En este caso, no existen las variables de entorno, pero si que existen variables que declararé aquí, como el SSID y el PASSWORD del AP o la ruta relativa de la base de datos.

### AppNetwork.h
Este archivo es el encargado de las conexiones, siendo esto crear el AP (con las credenciales del Config.h) y la conexión del ESP al router de casa para darle conectividad a Internet.

### Model.h
Aquí se trataran los datos, es decir, se tienen varios métodos, por ejemplo, ```getData()``` para coger los datos de la DB o ```saveData()``` para guardar datos.
Aquí irán definidos los métodos ```addProduct()``` para incluir productos o ```deleteProduct()``` para eliminarlos.

### View.h
En este archivo simplemente se define la constante ```index_html[]``` la cual tiene un html básico para mostrar en la ruta principal.

### Controller.h
Este sería el controlador de la aplicación. Como cualquier controlador, es el encargado de crear las rutas llamando a los métodos del controlador o/y la vista para conseguir lo que se espera (ver los productos, incluirlos, etc).

### StockManager.ino
Es el archivo que reune el resto de archivos y los inicializa. Sería como el archivo principal.