#include "vPrincipal.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Stock Manager</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100 text-gray-900 font-sans p-6">

    <div class="max-w-4xl mx-auto bg-white rounded-2xl shadow-lg p-6">
        <h1 class="text-3xl font-bold mb-6 text-center text-blue-600">Product List</h1>
        
        <div id="status" class="text-center text-sm text-gray-500 mb-4">Conectando...</div>

        <div class="mb-4 text-center sm:text-left">
            <button onclick="addProduct()" class="bg-green-500 text-white px-4 py-2 rounded-md hover:bg-green-600 shadow transition">
                + Add Product
            </button>
        </div>

        <div class="overflow-x-auto">
            <table class="min-w-full border border-gray-300 rounded-lg overflow-hidden">
                <thead class="bg-gray-200">
                    <tr>
                        <th class="py-2 px-4 border-b text-left">Name</th>
                        <th class="py-2 px-4 border-b text-center">Price</th>
                        <th class="py-2 px-4 border-b text-center">Stock</th>
                        <th class="py-2 px-4 border-b text-center">Actions</th>
                    </tr>
                </thead>
                <tbody id="productTableBody">
                    <tr><td colspan="4" class="text-center py-4 text-gray-500">Cargando datos...</td></tr>
                </tbody>
            </table>
        </div>
    </div>

    <script>
        const API_URL = '/api';

        // --- FUNCIONES DE CARGA ---
        async function loadProducts() {
            try {
                const res = await fetch(`${API_URL}/products`);
                const products = await res.json();
                renderTable(products);
                document.getElementById('status').innerText = '🟢 Sistema Online';
                document.getElementById('status').className = 'text-center text-sm text-green-600 mb-4';
            } catch (e) {
                document.getElementById('status').innerText = '🔴 Error de conexión';
                document.getElementById('status').className = 'text-center text-sm text-red-600 mb-4';
            }
        }

        function renderTable(products) {
            const tbody = document.getElementById('productTableBody');
            if (products.length === 0) {
                tbody.innerHTML = '<tr><td colspan="4" class="text-center py-4 text-gray-400">No hay productos. ¡Añade uno!</td></tr>';
                return;
            }

            let html = '';
            products.forEach(p => {
                html += `
                    <tr class="hover:bg-gray-50 text-center border-b last:border-none">
                        <td class="py-3 px-4 text-left font-medium">${p.name}</td>
                        <td class="py-3 px-4">${parseFloat(p.price).toFixed(2)} €</td>
                        <td class="py-3 px-4">
                            <span class="${p.stock < 5 ? 'text-red-600 font-bold' : 'text-gray-800'}">${p.stock}</span>
                        </td>
                        <td class="py-3 px-4 space-x-1 flex justify-center items-center flex-wrap gap-2">
                            <button onclick="changeStock(${p.id}, 'increase')" class="bg-green-500 text-white w-8 h-8 rounded hover:bg-green-600 font-bold">+</button>
                            <button onclick="changeStock(${p.id}, 'decrease')" class="bg-yellow-500 text-white w-8 h-8 rounded hover:bg-yellow-600 font-bold">−</button>
                            
                            <button onclick="editProduct(${p.id}, '${p.name}', ${p.price}, ${p.stock})" 
                                class="bg-blue-500 text-white px-3 py-1 rounded hover:bg-blue-600 text-sm">
                                Update
                            </button>
                            
                            <button onclick="deleteProduct(${p.id})" class="bg-red-500 text-white px-3 py-1 rounded hover:bg-red-600 text-sm">
                                Delete
                            </button>
                        </td>
                    </tr>
                `;
            });
            tbody.innerHTML = html;
        }

        // --- ACCIONES (CRUD) ---

        async function addProduct() {
            const name = prompt("Nombre del producto:");
            if (!name) return;
            
            const price = prompt("Precio (€):", "0.00");
            if (price === null) return;

            const stock = prompt("Stock inicial:", "1");
            if (stock === null) return;

            await fetch(`${API_URL}/add`, {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({ 
                    name: name, 
                    price: parseFloat(price), 
                    stock: parseInt(stock) 
                })
            });
            loadProducts();
        }

        async function editProduct(id, currentName, currentPrice, currentStock) {
            const name = prompt("Editar nombre:", currentName);
            if (name === null) return;

            const price = prompt("Editar precio:", currentPrice);
            if (price === null) return;

            const stock = prompt("Editar stock:", currentStock);
            if (stock === null) return;

            await fetch(`${API_URL}/update`, {  // OJO: Necesitamos añadir esta ruta al Controller
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({ 
                    id: id,
                    name: name, 
                    price: parseFloat(price), 
                    stock: parseInt(stock) 
                })
            });
            loadProducts();
        }

        async function deleteProduct(id) {
            if (!confirm("¿Seguro que quieres eliminar este producto?")) return;
            
            await fetch(`${API_URL}/delete`, {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({ id: id })
            });
            loadProducts();
        }

        async function changeStock(id, action) {
            await fetch(`${API_URL}/stock`, {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({ id: id, action: action })
            });
            loadProducts();
        }

        // Cargar al inicio y refrescar cada 5 segundos
        loadProducts();
        setInterval(loadProducts, 5000);

    </script>
</body>
</html>
)rawliteral";