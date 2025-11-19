const API_URL = '/api';

async function loadProducts() {
    try {
        const res = await fetch(`${API_URL}/products`);
        const products = await res.json();
        renderList(products);
        document.getElementById('status').innerText = 'Conectado al ESP32';
    } catch (e) {
        document.getElementById('status').innerText = 'Error de conexión';
    }
}

function renderList(products) {
    const container = document.getElementById('productList');
    container.innerHTML = '';
    
    // Creamos la tabla de productos
    let html = '<div class="card">';
    products.forEach(p => {
        html += `
            <div class="item">
                <div>${p.name}</div>
                <div>Stock: <span>${p.stock}</span></div>
            </div>
        `;
    });
    html += '</div>';
    container.innerHTML = html;
}

async function addProduct() {
    const name = document.getElementById('name').value;
    const stock = document.getElementById('stock').value;
    
    if(!name || !stock) return alert("Rellena todos los campos");

    await fetch(`${API_URL}/add`, {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({ name: name, price: 0, stock: parseInt(stock) })
    });

    document.getElementById('name').value = '';
    document.getElementById('stock').value = '';
    loadProducts(); // Recargar lista
}

// Cargar al inicio
loadProducts();