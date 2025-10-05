<?php

use App\Controllers\ProductController;

require __DIR__ . '/vendor/autoload.php';


$controller = new ProductController();

$action = $_GET['action'] ?? 'listProducts';

switch ($action) {
    case 'addForm':
        include __DIR__ . '/src/views/products/add.php';
        break;

    case 'addProduct':
        if (!empty($_POST['name']) && isset($_POST['price'], $_POST['stock'])) {
            $controller->addProduct($_POST['name'], (float)$_POST['price'], (int)$_POST['stock']);
        }
        header("Location: index.php?action=listProducts");
        exit;

    case 'updateProduct':
        $controller->updateProduct($_POST['id'], $_POST['name'], $_POST['price'], $_POST['stock']);
        header("Location: index.php?action=listProducts");
        break;
        
    case 'delete':
        if (isset($_GET['id'])) {
            $controller->deleteProduct((int)$_GET['id']);
        }
        header("Location: index.php?action=listProducts");
        exit;

    case 'increase':
        if (isset($_GET['id'])) {
            $controller->increaseStock((int)$_GET['id']);
        }
        header("Location: index.php?action=listProducts");
        exit;

    case 'decrease':
        if (isset($_GET['id'])) {
            $controller->decreaseStock((int)$_GET['id']);
        }
        header("Location: index.php?action=listProducts");
        exit;

    default:
        $controller->listProducts();
        break;
}
