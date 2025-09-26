<?php

class GestorUsuarios {
    private $usuarios = [];

    public function agregarUsuario(Usuario $usuario) {
        if (!$this->emailEsUnico($usuario->getEmail())) {
            throw new InvalidArgumentException("Email ya existe");
        }
        $this->usuarios[] = $usuario;
    }

    public function buscarPorEmail($email) {
        foreach ($this->usuarios as $usuario) {
            if ($usuario->getEmail() === $email) {
                return $usuario;
            }
        }
        return null;
    }

    public function getUsuariosMayores() {
        return array_filter($this->usuarios, function($usuario) {
            return $usuario->esMayorDeEdad();
        });
    }

    private function emailEsUnico($email) {
        return $this->buscarPorEmail($email) === null;
    }
}