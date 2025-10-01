<?php
namespace Models;

use App\Model;
use PDO;

class Usuario extends Model {
    public function crearTabla() {
        $this->db->exec("CREATE TABLE IF NOT EXISTS usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT,
            email TEXT UNIQUE,
            edad INTEGER
        )");
    }

    public function agregarUsuario(string $nombre, string $email, int $edad) {
        $stmt = $this->db->prepare("INSERT INTO usuarios (nombre, email, edad) VALUES (?, ?, ?)");
        $stmt->execute([$nombre, $email, $edad]);
        return $this->db->lastInsertId();
    }

    public function obtenerUsuarios(): array {
        $stmt = $this->db->query("SELECT * FROM usuarios");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
}
