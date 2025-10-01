<?php
require __DIR__ . '/vendor/autoload.php';

use Models\Usuario;

$usuario = new Usuario();
$usuario->crearTabla();
$id = $usuario->agregarUsuario("Juan", "juan@test.com", 25);

print_r($usuario->obtenerUsuarios());
