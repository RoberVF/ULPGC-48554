<?php

namespace Models;

use App\Model;
use PDO;

/**
 * Clase Producto para manejar operaciones CRUD sobre la tabla productos.
 *
 * @package Models
 */
class Producto extends Model
{
    /**
     * Crea la tabla productos si no existe.
     *
     * @return void
     */
    public function crearTabla(): void
    {
        $this->db->exec("CREATE TABLE IF NOT EXISTS productos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            precio REAL NOT NULL,
            stock INTEGER NOT NULL
        )");
    }

    /**
     * Agrega un producto a la base de datos.
     *
     * @param string $nombre
     * @param float $precio
     * @param int $stock
     * @return int ID del producto insertado
     */
    public function agregarProducto(string $nombre, float $precio, int $stock): int
    {
        $stmt = $this->db->prepare("INSERT INTO productos (nombre, precio, stock) VALUES (?, ?, ?)");
        $stmt->execute([$nombre, $precio, $stock]);
        return (int) $this->db->lastInsertId();
    }

    /**
     * Obtiene todos los productos de la base de datos.
     *
     * @return array
     */
    public function obtenerProductos(): array
    {
        $stmt = $this->db->query("SELECT * FROM productos");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Elimina un producto por ID.
     *
     * @param int $id
     * @return bool
     */
    public function eliminarProducto(int $id): bool
    {
        $stmt = $this->db->prepare("DELETE FROM productos WHERE id = ?");
        return $stmt->execute([$id]);
    }

    /**
     * Busca productos por nombre.
     *
     * @param string $nombre
     * @return array
     */
    public function buscarProducto(string $nombre): array
    {
        $stmt = $this->db->prepare("SELECT * FROM productos WHERE nombre LIKE ?");
        $stmt->execute(['%' . $nombre . '%']);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Elimina todos los productos de la tabla (para tests).
     */
    public function limpiarTabla()
    {
        $this->db->exec("DELETE FROM productos");
    }
}
