<?php

use App\Model\Product;
use PHPUnit\Framework\TestCase;

class ProductTest extends TestCase
{
    private $product;

    protected function setUp(): void
    {
        $this->product = new Product();
        $this->product->createTable();
        $this->product->cleanTable();
    }

    public function testAddFindProduct()
    {
        $id = $this->product->addProduct("Agua", 19.99, 10);
        $products = $this->product->findProducts();

        $this->assertNotEmpty($products);
        $this->assertEquals("Agua", $products[0]['name']);

        echo "\n[✔] Test Add and Find Product: Find ✅";
    }

    public function testDeleteProduct()
    {
        $id = $this->product->addProduct("Leche", 1.99, 20);
        $this->assertTrue($this->product->deleteProduct($id));

        $products = $this->product->findProducts();
        $this->assertEmpty($products);

        echo "\n[✔] Test Delete Product: Find ✅";
    }

    public function testFindProduct()
    {
        $this->product->addProduct("Pasta", 199.99, 5);
        $results = $this->product->findProduct("Past");
        $this->assertNotEmpty($results);
        $this->assertEquals("Pasta", $results[0]['name']);

        echo "\n[✔] Test Find Product: Find ✅";
    }
}
