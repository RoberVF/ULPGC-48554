<?php

class Reserva {
    private $fecha;
    private $personas;
    private $confirmada = false;

    public function __construct($fecha, $personas) {
        $this->fecha = $fecha;
        $this->personas = $personas;
    }

    public function confirmar() {
        if ($this->personas <= 0) {
            throw new InvalidArgumentException("Número de personas inválido");
        }
        $this->confirmada = true;
        return true;
    }

    public function estaConfirmada() { return $this->confirmada; }
    public function getPersonas() { return $this->personas; }
}