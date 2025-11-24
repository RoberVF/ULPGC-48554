# SPRINT 10. ARREGLO DE DECLARACIONES, MEJORA DEL MVC
### ARREGLO DE DECLARACIONES
Como se comentó en clase, había un error con la declaración de los nombres de los archivos. En el SPRINT 9, nombre todos los archivos con extension .h pero esto es incorrecto, dado que deben tener la extensión .h los archivos de declaraciones y nombrados con extensión .cpp los archivos con código real.

En este caso, he dejado el archivo Config.h con dicha extensión ya que es un archivo que solo tiene constantes de configuración y, en el resto de archivos, he declarado su versión .h donde solamente vendran las declaraciones de variables y funciones que voy a utilizar y su versión .cpp que será donde estará el código C++.

### MEJORA DEL MVC
En este apartado debo terminar el modelo para que contenga todos los métodos y la vista para que sea igual que la de nuestra aplicación original en PHP.
En primer lugar comenzaremos por el modelo. De la manera que hemos estructurado ahora la aplicación he declarado las variables y metodos en el Model.h y la funcionalidad de estas en el Model.cpp. Para ello, he replicado la funcionalidad de los métodos del modelo que teniamos en la aplicación de PHP y la he "traducido" a C++ para que funcione en el Arduino.
Por otra parte, para la vista he tomado la misma idea: poner lo que teniamos en la aplicación inicial en la actual. Aún así se deben de tomar en consideración cosas como que el ESP no puede ejecutar PHP (el bucle foreach de PHP no funciona aquí), y por tanto, tenemos que convertir esa lógica a JavaScript.

### EN CONCLUSIÓN
Tras terminar toda esta traducción tanto del modelo como de la vista y el renombre de la estructura de archivos, podríamos decir que ya tendríamos la aplicación preparada para subirla a la placa y comenzar a probar que todo funcione correctamente.
