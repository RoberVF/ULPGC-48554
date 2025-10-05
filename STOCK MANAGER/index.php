<?php

use App\Controllers\ProductController;

require __DIR__ . '/vendor/autoload.php';


$controller = new ProductController();

$action = $_GET['action'] ?? 'listProducts';

switch ($action) {
    case 'addForm':
        include __DIR__ . '/src/views/products/add.php';
        break;

    case 'deleteForm':
        include __DIR__ . '/src/views/products/delete.php';
        break;

    case 'addProduct':
        $controller->addProduct($_POST['name'], $_POST['price'], $_POST['stock']);
        header("Location: index.php?action=listProducts");
        break;

    case 'deleteProduct':
        $controller->deleteProduct($_POST['id']);
        header("Location: index.php?action=listProducts");
        break;

    default:
        $controller->listProducts();
        break;
}
