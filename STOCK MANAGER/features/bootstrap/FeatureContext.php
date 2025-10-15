<?php

use App\Controllers\ProductController;
use App\Model\Product;
use Behat\Behat\Context\Context;
use Behat\Gherkin\Node\TableNode;
use PHPUnit\Framework\Assert;

/**
 * Defines application features from the specific context.
 */
class FeatureContext implements Context
{
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    private $controller;
    private $productModel;

    public function __construct()
    {
        // Instanciamos tanto el controlador para las acciones como el modelo para las verificaciones.
        $this->controller = new ProductController();
        $this->productModel = new Product();
    }

    /**
     * @BeforeScenario
     */
    public function cleanDatabase()
    {
        // Limpia la base de datos antes de cada escenario para asegurar el aislamiento.
        $this->productModel->cleanTable();
    }

    // -------------------------------------------------------------------------
    // PASOS 'GIVEN' (PREPARACION)
    // -------------------------------------------------------------------------

    /**
     * @Given el inventario esta vacio
     */
    public function elInventarioEstaVacio()
    {
        // Este paso esta cubierto por el @BeforeScenario, pero es bueno tenerlo
    }

    /**
     * @Given /^existe un producto llamado "([^"]*)" con stock (\d+)$/
     */
    public function existeUnProductoLlamadoConStock($name, $stock)
    {
        $this->controller->addProduct($name, 1.00, (int) $stock);
    }

    /**
     * @Given /^el inventario contiene los siguientes productos:$/
     */
    public function elInventarioContieneLosSiguientesProductos(TableNode $table)
    {
        foreach ($table->getHash() as $row) {
            $this->controller->addProduct(
                $row['name'],
                (float) $row['price'],
                (int) $row['stock']
            );
        }
    }

    // -------------------------------------------------------------------------
    // PASOS 'WHEN' Y 'THEN'
    // -------------------------------------------------------------------------

    /**
     * @When /^agrego un producto llamado "([^"]*)" con precio "([^"]*)" y stock "([^"]*)"$/
     */
    public function agregoUnProductoLlamadoConPrecioYStock($name, $price, $stock)
    {
        // Llama al controlador para ejecutar la accion de agregar un producto.
        $this->controller->addProduct($name, (float) $price, (int) $stock);
    }

    /**
     * @Then /^el producto "([^"]*)" debe existir en el inventario con un stock de (\d+)$/
     */
    public function elProductoDebeExistirEnElInventarioConUnStockDe($name, $stock)
    {
        // Busca el producto en la base de datos usando el modelo.
        // Es importante usar una busqueda exacta aqui.
        $products = $this->productModel->findProductByName($name);

        // Verificamos que el producto exista y que el stock sea correcto.
        Assert::assertCount(1, $products, "El producto '$name' no fue encontrado en la base de datos.");
        Assert::assertEquals((int) $stock, $products[0]['stock'], "El stock del producto '$name' no coincide.");
    }
}
