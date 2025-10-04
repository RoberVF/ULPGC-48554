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
    }
}
