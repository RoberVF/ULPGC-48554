<?php

namespace App\Controllers;

use App\Model\Product;

/**
 * @class ProductController
 * @brief Controlador para manejar operaciones relacionadas con productos.
 *
 * CRUD y manejo de productos en la aplicacion entre modelo y vista.
 */
class ProductController
{
    /**
     * @var Product $productModel Instancia del modelo Product.
     */
    private Product $productModel;

    /**
     * Constructor - Inicializamos el modelo Product.
     */
    public function __construct()
    {
        $this->productModel = new Product();
        $this->productModel->createTable();
    }

    /**
     * @brief Muestra la lista de todos los products.
     *
     * @return array Lista de productos de la db.
     */
    public function listProducts(): array
    {
        return $this->productModel->findProducts();
    }

    /**
     * @brief Meter nuevos products en la db.
     *
     * @param string $name Nombre del product.
     * @param float $price Precio del product.
     * @param int $stock Cantidad que metemos (Stock).
     * @return int ID del nuevo product.
     */
    public function addProduct(string $name, float $price, int $stock): int
    {
        return $this->productModel->addProduct($name, $price, $stock);
    }

    /**
     * @brief Elimina un product por el ID.
     *
     * @param int $id ID del product.
     * @return bool True si sale bien, False si no.
     */
    public function deleteProduct(int $id): bool
    {
        return $this->productModel->deleteProduct($id);
    }

    /**
     * @brief Busca un product por nombre (o parte del nombre).
     *
     * @param string $name Nombre o parte del nombre a buscar.
     * @return array Array de products que coinciden.
     */
    public function searchProduct(string $name): array
    {
        return $this->productModel->findProduct($name);
    }
}
