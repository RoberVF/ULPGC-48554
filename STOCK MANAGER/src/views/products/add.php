<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Add Product</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100 p-6">
    <div class="max-w-md mx-auto bg-white rounded-xl shadow-md p-6">
        <h1 class="text-2xl font-bold text-center mb-4">Add Product</h1>

        <form method="POST" action="../index.php?action=addProduct" class="space-y-4">
            <div>
                <label class="block text-sm font-medium text-gray-700">Name</label>
                <input type="text" name="name" required class="w-full p-2 border rounded-md focus:ring focus:ring-blue-200">
            </div>

            <div>
                <label class="block text-sm font-medium text-gray-700">Price</label>
                <input type="number" step="0.01" name="price" required class="w-full p-2 border rounded-md focus:ring focus:ring-blue-200">
            </div>

            <div>
                <label class="block text-sm font-medium text-gray-700">Stock</label>
                <input type="number" name="stock" required class="w-full p-2 border rounded-md focus:ring focus:ring-blue-200">
            </div>

            <button type="submit" class="w-full bg-blue-500 text-white py-2 rounded-md hover:bg-blue-600">Add Product</button>
        </form>

        <div class="mt-4 text-center">
            <a href="../index.php?action=listProducts" class="text-blue-600 hover:underline">Back to list</a>
        </div>
    </div>
</body>
</html>
