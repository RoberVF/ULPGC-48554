<?php
require_once 'src/Usuario.php';
require_once 'src/GestorUsuarios.php';

use PHPUnit\Framework\TestCase;

class GestorUsuariosTest extends TestCase {
    private $gestor;

    protected function setUp(): void {
        $this->gestor = new GestorUsuarios();
    }

    public function testAgregarYBuscarUsuario() {
        // Arrange
        $usuario = new Usuario("Juan", "juan@test.com", 25);
        
        // Act
        $this->gestor->agregarUsuario($usuario);
        $usuarioEncontrado = $this->gestor->buscarPorEmail("juan@test.com");
        
        // Assert
        $this->assertNotNull($usuarioEncontrado);
        $this->assertEquals("Juan", $usuarioEncontrado->getNombre());
    }

    public function testEmailDuplicadoLanzaExcepcion() {
        $usuario1 = new Usuario("Ana", "ana@test.com", 30);
        $usuario2 = new Usuario("Ana2", "ana@test.com", 22);

        $this->gestor->agregarUsuario($usuario1);
        
        $this->expectException(InvalidArgumentException::class);
        $this->gestor->agregarUsuario($usuario2);
    }

    public function testGetUsuariosMayores() {
        $menor = new Usuario("Niño", "nino@test.com", 15);
        $mayor1 = new Usuario("Adulto1", "ad1@test.com", 25);
        $mayor2 = new Usuario("Adulto2", "ad2@test.com", 30);

        $this->gestor->agregarUsuario($menor);
        $this->gestor->agregarUsuario($mayor1);
        $this->gestor->agregarUsuario($mayor2);

        $mayores = $this->gestor->getUsuariosMayores();

        $this->assertCount(2, $mayores);
        $this->assertContains($mayor1, $mayores);
        $this->assertContains($mayor2, $mayores);
        $this->assertNotContains($menor, $mayores);
    }
}