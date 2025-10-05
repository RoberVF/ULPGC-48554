<?php

use App\Controllers\ProductController;

require __DIR__ . '/vendor/autoload.php';


$controller = new ProductController();

// Add some products for demo
$controller->addProduct("Water", 1.99, 30);
$controller->addProduct("Milk", 2.49, 15);
$controller->addProduct("Nutella", 2.49, 1);

// Get list and show
$products = $controller->listProducts();

// Load view
require __DIR__ . '/src/Views/products/list.php';
