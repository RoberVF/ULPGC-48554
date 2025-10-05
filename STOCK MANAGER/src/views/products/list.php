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

        <table class="min-w-full border border-gray-300 rounded-lg overflow-hidden">
            <thead class="bg-gray-200">
                <tr>
                    <th class="py-2 px-4 border-b">ID</th>
                    <th class="py-2 px-4 border-b">Name</th>
                    <th class="py-2 px-4 border-b">Price</th>
                    <th class="py-2 px-4 border-b">Stock</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($products as $p): ?>
                    <tr class="hover:bg-gray-50">
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['id']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['name']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['price']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['stock']) ?></td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </div>

</body>
</html>