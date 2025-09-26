<?php

class Usuario {
    private $nombre;
    private $email;
    private $edad;

    public function __construct($nombre, $email, $edad) {
        $this->nombre = $nombre;
        $this->email = $email;
        $this->edad = $edad;
    }

    public function esMayorDeEdad() {
        return $this->edad >= 18;
    }

    public function getNombre() { return $this->nombre; }
    public function getEmail() { return $this->email; }
    public function getEdad() { return $this->edad; }
}

