<?php

use PHPUnit\Framework\TestCase;
use Models\Producto;

class ProductoTest extends TestCase
{
    private $producto;

    protected function setUp(): void
    {
        $this->producto = new Producto();
        $this->producto->crearTabla();
        $this->producto->limpiarTabla();
    }

    public function testAgregarYObtenerProducto()
    {
        $id = $this->producto->agregarProducto("Agua", 19.99, 10);
        $productos = $this->producto->obtenerProductos();

        $this->assertNotEmpty($productos);
        $this->assertEquals("Agua", $productos[0]['nombre']);

        echo "\n[✔] Test Agregar y Obtener Producto: Bien ✅";
    }

    public function testEliminarProducto()
    {
        $id = $this->producto->agregarProducto("Raton", 9.99, 20);
        $this->assertTrue($this->producto->eliminarProducto($id));

        $productos = $this->producto->obtenerProductos();
        $this->assertEmpty($productos);

        echo "\n[✔] Test Eliminar Producto: Bien ✅";
    }

    public function testBuscarProducto()
    {
        $this->producto->agregarProducto("Monitor", 199.99, 5);
        $resultados = $this->producto->buscarProducto("Moni");
        $this->assertNotEmpty($resultados);
        $this->assertEquals("Monitor", $resultados[0]['nombre']);

        echo "\n[✔] Test Buscar Producto: Bien ✅";
    }
}
