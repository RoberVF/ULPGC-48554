<?php

/**
 * @file list.php
 * @brief Vista para mostrar la lista de productos.
 *
 * @param array $products Array de productos a mostrar.
 */
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Stock Manager</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>

<body class="bg-gray-100 text-gray-900 font-sans p-6">

    <div class="max-w-3xl mx-auto bg-white rounded-2xl shadow-lg p-6">
        <h1 class="text-3xl font-bold mb-6 text-center text-blue-600">Product List</h1>
        <div class="mb-4">
            <a href="index.php?action=addForm" class="bg-green-500 text-white px-4 py-2 rounded-md hover:bg-green-600">Add Product</a>
        </div>
        <table class="min-w-full border border-gray-300 rounded-lg overflow-hidden">
            <thead class="bg-gray-200">
                <tr>
                    <th class="py-2 px-4 border-b">Name</th>
                    <th class="py-2 px-4 border-b">Price</th>
                    <th class="py-2 px-4 border-b">Stock</th>
                    <th class="py-2 px-4 border-b text-center">Actions</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($products as $p): ?>
                    <tr class="hover:bg-gray-50">
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['name']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['price']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['stock']) ?></td>
                        <td class="py-2 px-4 border-b text-center">
                            <button onclick="confirmDelete(<?= $p['id'] ?>)"
                                class="bg-red-500 text-white px-3 py-1 rounded-md hover:bg-red-600 transition">
                                Delete
                            </button>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
        <form id="deleteForm" method="POST" action="index.php?action=deleteProduct" style="display:none;">
            <input type="hidden" name="id" id="deleteId">
        </form>
    </div>

</body>
<script>
    /**
     * Muestra una ventana de confirmacion antes de eliminar el producto.
     * Si el usuario acepta, envia un formulario oculto al servidor para eliminarlo.
     * @param {number} id - ID del producto a eliminar
     */
    function confirmDelete(id) {
        if (confirm("¿Seguro que quieres eliminar este producto?")) {
            document.getElementById("deleteId").value = id;
            document.getElementById("deleteForm").submit();
        }
    }
</script>

</html>