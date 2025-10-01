<?php
use PHPUnit\Framework\TestCase;
use Models\Usuario;

class UsuarioTest extends TestCase {
    private $usuario;

    protected function setUp(): void {
        $this->usuario = new Usuario();
        $this->usuario->crearTabla();
    }

    public function testAgregarYObtenerUsuario() {
        $id = $this->usuario->agregarUsuario("Ana", "ana@test.com", 30);
        $usuarios = $this->usuario->obtenerUsuarios();
        $this->assertNotEmpty($usuarios);
        $this->assertEquals("Ana", $usuarios[0]['nombre']);
    }
}
