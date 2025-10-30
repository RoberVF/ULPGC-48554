# SPRINT 6. DOCUMENTACION BDD BASADA EN TDD E INTEGRACION DE MINK {#sprint6_page}

### Sobre Mink y sus drivers
**Mink** es una biblioteca de PHP de codigo abierto que actua como un controlador o emulador de navegador para aplicaciones web. Con esta herramienta se pueden simular las interacciones reales de un usuario al "clicar en la web directamente".

**Mink** traducira los pasos del lenguaje Gherkin de Behat (ej., "Cuando hago clic en el boton 'Incluir Producto'") en acciones reales del navegador. Para ello, debemos utilizar un driver para el navegador llamado **Goutte**. Este driver es un cliente simple HTTP para hacer peticiones sin Javascript, perfecto para nuestro proyecto ya que no estamos utilizando JS.

He visto que existen drivers mas potentes como **ChromeDriver** o **Selenium2Driver** que si que permiten controlar un navegador real como *Chrome* para ejecutar las pruebas dependientes de Javascript pero no creo que sea necesario utilizar herramientas mas complejas ya que con lo que ofrece **Goutte** sera suficiente.

Utilizando **Mink**, la capa BDD hecha con **Behat** podra validar el flujo completo de la aplicacion, incluyendo ahi la interfaz y no quedandonos solamente en la logica del backend.

### Documentacion de BDD basada en TDD
Actualmente, nuestro proyecto esta siguiendo una estructura de pruebas por capas, donde TDD y BDD se complementan en lugar de sustitutirse.

En cuanto al TDD, implementado con **PHPUnit**, buscammos que cada unidad de codigo en si misma, siendo estas clases y metodos, funcionen segun lo previsto. Esto implica por ejemplo que un metodo para insertar productos en la base de datos, esta creando una nueva fila en ella o que un metodo pensado para decrementar el stock de un producto lo esta decrementando correctamente.

Por otra parte, tenemos el BDD, implementado con **Behat**, lo cual comprueba el flujo de trabajo completo a traves de la metodologia MVC. Esto implica que no solamente se valide el metodo de insertar el producto sino que valide el comportamiento completo del sistema desde la perspectiva del usuario (se integran los datos en el formulario para crear un nuevo producto, se recibe la solicitud en el controlador y el producto aparece correctamente listado en la lista de productos totales de la vista).

