<?php
use PHPUnit\Framework\TestCase;
require_once 'src/Calculadora.php';

class CalculadoraTest extends TestCase {
    private $calculadora;

    // setUp se ejecuta antes de cada test
    protected function setUp(): void {
        $this->calculadora = new Calculadora();
    }

    public function testSumar() {
        // Arrange
        $a = 5;
        $b = 3;
        
        // Act
        $resultado = $this->calculadora->sumar($a, $b);
        
        // Assert
        $this->assertEquals(8, $resultado);
    }

    public function testRestar() {
        $resultado = $this->calculadora->restar(10, 4);
        $this->assertEquals(6, $resultado);
    }

    public function testMultiplicar() {
        $resultado = $this->calculadora->multiplicar(7, 6);
        $this->assertEquals(42, $resultado);
    }

    public function testDividir() {
        $resultado = $this->calculadora->dividir(15, 3);
        $this->assertEquals(5, $resultado);
    }

    public function testDividirPorCeroLanzaExcepcion() {
        $this->expectException(InvalidArgumentException::class);
        $this->calculadora->dividir(10, 0);
    }

    // Data Provider para múltiples casos de prueba
    public static function proveedorSumas() {
        return [
            [1, 1, 2],
            [0, 0, 0],
            [-1, 1, 0],
            [100, 200, 300]
        ];
    }

    /**
     * @dataProvider proveedorSumas
     */
    public function testSumarConMultipleData($a, $b, $esperado) {
        $resultado = $this->calculadora->sumar($a, $b);
        $this->assertEquals($esperado, $resultado);
    }
}