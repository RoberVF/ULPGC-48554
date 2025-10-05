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

    <div class="max-w-4xl mx-auto bg-white rounded-2xl shadow-lg p-6">
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
                    <tr class="hover:bg-gray-50 text-center">
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['name']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['price']) ?></td>
                        <td class="py-2 px-4 border-b"><?= htmlspecialchars($p['stock']) ?></td>
                        <td class="py-2 px-4 border-b text-center space-x-2">
                            <form method="POST" action="index.php?action=increase&id=<?= $p['id'] ?>" class="inline">
                                <button class="bg-green-500 text-white px-3 py-1 rounded-lg hover:bg-green-600">+</button>
                            </form>
                            <form method="POST" action="index.php?action=decrease&id=<?= $p['id'] ?>" class="inline">
                                <button class="bg-yellow-500 text-white px-3 py-1 rounded-lg hover:bg-yellow-600">−</button>
                            </form>
                            <button class="bg-blue-500 text-white px-3 py-1 rounded-lg hover:bg-blue-600"
                                onclick="updateProduct(<?= $p['id'] ?>, '<?= htmlspecialchars($p['name']) ?>', <?= $p['price'] ?>, <?= $p['stock'] ?>)">
                                Update
                            </button>
                            <form method="POST" action="index.php?action=delete&id=<?= $p['id'] ?>" onsubmit="return confirm('¿Seguro que deseas eliminar este producto?');" class="inline">
                                <button class="bg-red-500 text-white px-3 py-1 rounded-lg hover:bg-red-600">Delete</button>
                            </form>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
        <!-- <form id="deleteForm" method="POST" action="index.php?action=deleteProduct" style="display:none;">
            <input type="hidden" name="id" id="deleteId">
        </form> -->
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

    /**
     * Muestra alerts para actualizar los datos del producto y envia un formulario al servidor.
     * @param {number} id - ID del producto a actualizar
     * @param {string} currentName - Nombre actual del producto
     * @param {number} currentPrice - Precio actual del producto
     * @param {number} currentStock - Stock actual del producto
     */
    function updateProduct(id, currentName, currentPrice, currentStock) {
        const name = prompt("Nuevo nombre:", currentName);
        if (name === null) return;

        const price = parseFloat(prompt("Nuevo precio:", currentPrice));
        if (isNaN(price)) return alert("Precio no valido");

        const stock = parseInt(prompt("Nuevo stock:", currentStock));
        if (isNaN(stock)) return alert("Stock no valido");

        // Creamos un formulario dinamico para enviar el POST
        const form = document.createElement("form");
        form.method = "POST";
        form.action = "index.php?action=updateProduct";

        const fields = {
            id,
            name,
            price,
            stock
        };
        for (const key in fields) {
            const input = document.createElement("input");
            input.type = "hidden";
            input.name = key;
            input.value = fields[key];
            form.appendChild(input);
        }

        document.body.appendChild(form);
        form.submit();
    }
</script>

</html>