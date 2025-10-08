# SPRINT 4
### Por lo que he visto trabajando con TDD:
- Primero se escribe el test que falla (el rojo)
- Despues se escribe lo minimo para que el test funcione correctamente (el verde)
- Se refactoriza el codigo para que siga siendo verde pero se mejora el diseno todo lo posible

Entonces, se busca que el codigo funcione como debe, y que las clases y los metodos 
esten bien estructurados.

En el proyecto que estamos tratando, seguiriamos este flujo:
- Hacemos un test para el/los modelo, controlador, etc
- Se comprueba que los metodos funcionen, es decir, que addProduct() inserte productos,
	deleteProduct() los elimine, etc.

### Por lo que he buscado acerca del BDD:
- Aqui no buscamos que cada cosa funcione independientemente sino que por ejemplo si
	tenemos productos en el sistema, cuando elimino uno este debe desaparecer de la db.

Entonces, ya no solo comprobaremos que deleteProduct() elimine un producto sino que 
cuando en la web pulsamos el boton de eliminar se elimine un producto, ya no aparezca en 
la vista, ya no aparezca en la base de datos, etc. Asi, comprobaremos el MVC al completo, 
no solo el metodo del modelo.

A diferencia del TDD, el BDD si que lo he trabajado en empresas privadas y tengo un 
conocimiento mas cercano hacia el. Al final del dia, si debemos crear una funcionalidad 
en la aplicacion, esta funcionalidad debe ser testeada antes de pasarla a produccion 
y la manera de testearlo es "haciendo lo que hace el usuario final".
Creo que el paradigma BDD es interesante e indispensable en cualquier tipo de aplicacion 
pero tambien veo muy interesante seguir realizando TDD a los metodos que se creen en la 
aplicacion.