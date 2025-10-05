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

    public function testUpdateProduct()
    {
        $id = $this->product->addProduct("Old", 5.00, 10);
        $this->product->updateProduct($id, "New", 9.99, 20);

        $products = $this->product->findProducts();
        $this->assertEquals("New", $products[0]['name']);
        $this->assertEquals(20, $products[0]['stock']);
        echo "\n[✔] Test Update Product ✅";
    }

    public function testIncreaseDecreaseStock()
    {
        $id = $this->product->addProduct("Water", 1.00, 5);
        $this->product->increaseStock($id);
        $this->product->decreaseStock($id);

        $product = $this->product->findProducts()[0];
        $this->assertEquals(5, $product['stock']);
        echo "\n[✔] Test Increase/Decrease Stock ✅";
    }
}
