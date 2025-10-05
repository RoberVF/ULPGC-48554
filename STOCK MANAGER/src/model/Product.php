<?php

namespace App\Model;

use App\Model;
use PDO;

/**
 * Clase Product para manejar operaciones CRUD sobre la tabla products.
 *
 * @package Models
 */
class Product extends Model
{
    /**
     * Crea la tabla products si no existe.
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
     * Agrega un product a la base de datos.
     *
     * @param string $name
     * @param float $price
     * @param int $stock
     * @return int ID del product insertado
     */
    public function addProduct(string $name, float $price, int $stock): int
    {
        $stmt = $this->db->prepare("INSERT INTO products (name, price, stock) VALUES (?, ?, ?)");
        $stmt->execute([$name, $price, $stock]);
        return (int) $this->db->lastInsertId();
    }

    /**
     * Obtiene todos los products de la base de datos.
     *
     * @return array
     */
    public function findProducts(): array
    {
        $stmt = $this->db->query("SELECT * FROM products");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    /**
     * Elimina un product por ID.
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
     * Busca products por nombre.
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
     * Elimina todos los products de la tabla (para tests).
     */
    public function cleanTable()
    {
        $this->db->exec("DELETE FROM products");
    }

    /**
     * Actualiza los datos de un producto.
     *
     * @param int $id
     * @param string $name
     * @param float $price
     * @param int $stock
     * @return bool True si se actualiza correctamente.
     */
    public function updateProduct(int $id, string $name, float $price, int $stock): bool
    {
        $stmt = $this->db->prepare("UPDATE products SET name = ?, price = ?, stock = ? WHERE id = ?");
        return $stmt->execute([$name, $price, $stock, $id]);
    }

    /**
     * Incrementa el stock de un producto.
     *
     * @param int $id
     * @return bool
     */
    public function increaseStock(int $id): bool
    {
        $stmt = $this->db->prepare("UPDATE products SET stock = stock + 1 WHERE id = ?");
        return $stmt->execute([$id]);
    }

    /**
     * Disminuye el stock de un producto (sin bajar de cero).
     *
     * @param int $id
     * @return bool
     */
    public function decreaseStock(int $id): bool
    {
        $stmt = $this->db->prepare("UPDATE products SET stock = CASE WHEN stock > 0 THEN stock - 1 ELSE 0 END WHERE id = ?");
        return $stmt->execute([$id]);
    }
}
