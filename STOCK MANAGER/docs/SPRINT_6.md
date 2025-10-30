# SPRINT 6. DOCUMENTACION BDD BASADA EN TDD E INTEGRACION DE MINK {#sprint6_page}

### Documentacion de BDD basada en TDD
Actualmente, nuestro proyecto esta siguiendo una estructura de pruebas por capas, donde TDD y BDD se complementan en lugar de sustitutirse.

En cuanto al TDD, implementado con **PHPUnit**, buscammos que cada unidad de codigo en si misma, siendo estas clases y metodos, funcionen segun lo previsto. Esto implica por ejemplo que un metodo para insertar productos en la base de datos, esta creando una nueva fila en ella o que un metodo pensado para decrementar el stock de un producto lo esta decrementando correctamente.

Por otra parte, tenemos el BDD, implementado con **Behat**, lo cual comprueba el flujo de trabajo completo a traves de la metodologia MVC. Esto implica que no solamente se valide el metodo de insertar el producto sino que valide el comportamiento completo del sistema desde la perspectiva del usuario (se integran los datos en el formulario para crear un nuevo producto, se recibe la solicitud en el controlador y el producto aparece correctamente listado en la lista de productos totales de la vista).

### Sobre Mink y sus drivers
**Mink** es una biblioteca de PHP de codigo abierto que actua como un controlador o emulador de navegador para aplicaciones web. Con esta herramienta se pueden simular las interacciones reales de un usuario al "clicar en la web directamente".

**Mink** traducira los pasos del lenguaje Gherkin de Behat (ej., "Cuando hago clic en el boton 'Incluir Producto'") en acciones reales del navegador. Para ello, debemos utilizar un driver para el navegador llamado **Goutte**. Este driver es un cliente simple HTTP para hacer peticiones sin Javascript, perfecto para nuestro proyecto ya que no estamos utilizando JS.

He visto que existen drivers mas potentes como **ChromeDriver** o **Selenium2Driver** que si que permiten controlar un navegador real como *Chrome* para ejecutar las pruebas dependientes de Javascript pero no creo que sea necesario utilizar herramientas mas complejas ya que con lo que ofrece **Goutte** sera suficiente.

Utilizando **Mink**, la capa BDD hecha con **Behat** podra validar el flujo completo de la aplicacion, incluyendo ahi la interfaz y no quedandonos solamente en la logica del backend.


#### Instalacion de Mink y Goutte
Para instalar **Mink** y **Goutte** nos bastara con requerirlo con composer en el composer.json:
```composer require --dev behat/mink behat/mink-goutte-driver```
Esto instalara la ultima version actualizada de ambos. Hay que tener en cuenta que he debido de eliminar *composer.lock* para poder realizar la instalacion correctamente.

#### Configuracion de Mink
Para configurar **Mink** he tenido que crear en la raiz del proyecto el archivo ```behat.yml```. Este archivo sera el que le especifique a **Mink** en que lugar debe actuar para poder simular la navegacion.
Ademas, se debe de especificar cual sera el contexto del proyecto, en nuestro caso ```FeatureContext```, que utilizaremos **Goute** y cual sera la url base del proyecto.

#### Problemas en el uso de Mink
El avance del SPRINT 6 esta bloqueado debido a un conflicto de dependencias irresoluble en **Composer**. La version actual de **Behat** (^3.25) requiere librerias de **Symfony** modernas (v5+), pero la extension de **Mink** (*mink-extension*) que estoy intentando instalar solo encuentra versiones antiguas que dependen de **Symfony** v2/v3. **Composer** no puede trabajar con estas diferentes versiones, lo que impide instalar las herramientas de testing web (**Mink/Goutte**) necesarias para continuar.

