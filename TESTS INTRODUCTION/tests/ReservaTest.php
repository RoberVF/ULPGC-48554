<?php
require_once 'src/Reserva.php';

use PHPUnit\Framework\TestCase;

class ReservaTest extends TestCase
{
    public function testReservaSePuedeConfirmar()
    {
        // Arrange
        $reserva = new Reserva('2024-01-01', 4);

        // Act
        $resultado = $reserva->confirmar();

        // Assert
        $this->assertTrue($resultado);
        $this->assertTrue($reserva->estaConfirmada());
    }

    public function testReservaConCeroPersonasNoSePuedeConfirmar()
    {
        $reserva = new Reserva('2024-01-01', 0);

        $this->expectException(InvalidArgumentException::class);
        $reserva->confirmar();
    }

    public function testReservaRecienCreadaNoEstaConfirmada()
    {
        $reserva = new Reserva('2024-01-01', 2);

        $this->assertFalse($reserva->estaConfirmada());
    }
}
