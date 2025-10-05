<?php

use App\Controllers\ProductController;
use App\Model\Product;
use PHPUnit\Framework\TestCase;

class ProductControllerTest extends TestCase
{
    private $controller;

    protected function setUp(): void
    {
        $this->controller = new ProductController();
        $model = new Product();
        $model->createTable();
        $model->cleanTable();
    }

    public function testAddAndListProducts()
    {
        $this->controller->addProduct("Pan", 2.50, 15);
        $products = $this->controller->listProducts();

        $this->assertNotEmpty($products);
        $this->assertEquals("Pan", $products[0]['name']);
        echo "\n[✔] Controller Test: Add and List ✅";
    }
}
