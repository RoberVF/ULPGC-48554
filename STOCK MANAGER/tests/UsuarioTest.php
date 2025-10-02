<?php

use PHPUnit\Framework\TestCase;
use Models\Usuario;

class UsuarioTest extends TestCase
{
    private $usuario;

    protected function setUp(): void
    {
        $this->usuario = new Usuario();
        $this->usuario->crearTabla();
    }

    public function testAgregarYObtenerUsuario()
    {
        $id = $this->usuario->agregarUsuario("Juan", uniqid("juan")."@test.com", 30);
        $usuarios = $this->usuario->obtenerUsuarios();
        $this->assertNotEmpty($usuarios);
        $this->assertEquals("Juan", $usuarios[0]['nombre']);
    }
}
