<?php

namespace Models;

use App\Model;
use PDO;

/**
 * Clase Producto para manejar operaciones CRUD sobre la tabla productos.
 *
 * @package Models
 */
class Product extends Model
{
    /**
     * Crea la tabla productos si no existe.
     *
     * @return void
     */
    public function createTable(): void
    {
        $this->db->exec("CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            price REAL NOT NULL,
            stock INTEGER NOT NULL
        )");
    }

    /**
     * Agrega un producto a la base de datos.
     *
     * @param string $name
     * @param float $price
     * @param int $stock
     * @return int ID del producto insertado
     */
    public function addProduct(string $name, float $price, int $stock): int
    {
        $stmt = $this->db->prepare("INSERT INTO products (name, price, stock) VALUES (?, ?, ?)");
        $stmt->execute([$name, $price, $stock]);
        return (int) $this->db->lastInsertId();
    }

    /**
     * Obtiene todos los productos de la base de datos.
     *
     * @return array
     */
    public function findProducts(): array
    {
        $stmt = $this->db->query("SELECT * FROM products");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Elimina un producto por ID.
     *
     * @param int $id
     * @return bool
     */
    public function deleteProduct(int $id): bool
    {
        $stmt = $this->db->prepare("DELETE FROM products WHERE id = ?");
        return $stmt->execute([$id]);
    }

    /**
     * Busca productos por nombre.
     *
     * @param string $name
     * @return array
     */
    public function findProduct(string $name): array
    {
        $stmt = $this->db->prepare("SELECT * FROM products WHERE name LIKE ?");
        $stmt->execute(['%' . $name . '%']);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Elimina todos los productos de la tabla (para tests).
     */
    public function cleanTable()
    {
        $this->db->exec("DELETE FROM products");
    }
}
