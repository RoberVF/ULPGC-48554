# STOCK MANAGER (PHP + SQLITE)

Stock Manager es una aplicación local para gestionar el inventario de la despensa utilizando PHP y SQLite.

El sistema permite registrar productos cuando se almacenan y descontarlos cuando se desechan, llevando un control de stock en tiempo real.
Además, ofrece una funcionalidad de comparación de precios entre supermercados para ayudar a decidir en qué lugar conviene comprar cada producto.

## Funcionamiento

### Escaneo de Productos para Almacenarlos
- Se pone la aplicación en modo ALMACENAR.
- El usuario escanea el código de barras con el lector situado en la despensa.
- El sistema busca ese código en la base de datos:
- - Si existe: incrementa el stock de ese producto.
- - Si no existe: solicita al usuario nombre del producto, supermercado donde se ha comprado y precio en ese supermercado. Luego se registra en base de datos.

Importante: Si el mismo producto se compra en otro supermercado y tiene otro código de barras, se registrará como otro producto pero con el mismo nombre. Esto permite comparar precios entre supermercados.

### Escaneo de Productos para Desecharlos
- Se pone la aplicación en modo DESCARTAR.
- El usuario escanea el producto antes de tirarlo a la basura.
- El sistema reduce el stock:
- - Si llega a 0: El producto entra en una lista para comprarlo.
- - Si queda en negativo: indica que se han consumido productos que no estaban registrados como entrada (útil para ajustar stock y planificar compras).

### Comparación de Precios y Lista de Compra
- Cada producto tiene precio asociado por supermercado.
- El sistema genera automáticamente una lista de compra optimizada, indicando:
- - Qué productos hay que reponer (los que están en stock negativo o por debajo de un mínimo definido).
- - En qué supermercado es más barato comprar cada uno.

### Soporte para Múltiples Lectores
- Se pueden usar varios lectores en diferentes ubicaciones (por ejemplo, uno en la despensa y otro en la cocina junto al cubo de basura).
- Cada lector tiene asignado un modo fijo y este puede cambiarse desde la interfaz.
- Es posible establecer varios lectores en un mismo modo (por ejemplo, dos lectores en modo ALMACENAR y tres lectores en modo DESCARTAR).

## Posibles problemas y soluciones
- Producto escaneado que no existe en la base de datos: Solicitar datos al usuario y registrarlo inmediatamente.
- Productos idénticos con diferentes códigos de barras: Relacionar productos por nombre genérico en la base de datos, de forma que se pueda comparar el precio entre supermercados.
- Stock negativo: Permitir stock negativo para que se refleje en la lista de compra como cantidad pendiente de reponer.
- Confusión entre lectores de entrada y salida: Identificar cada lector y mostrar su modo en una pantalla LCD.
- Producto sin código de barras: Imposible escanearlo. Registro manual en la aplicación.
- Errores por doble escaneo: Cada vez que se escanee, ya sea para almacenarlos o desecharlos, mostrar el nombre de este producto en la pantalla LCD y realizar un pitido con un buzzer.
- Precios desactualizados: Los precios de los supermercados cambian constantemente. La aplicación debe tener la posibilidad de actualizar los precios rápidamente. Se podría valorar en un futuro la posibilidad de utilizar web scrapping para conseguir el valor actualizado de los precios.


## A futuro...
Se piensa instalar este programa en una placa arduino NodeMCU con acceso a internet y disponibilidad de lector de codigo de barras para dar asi una funcionalidad real.
