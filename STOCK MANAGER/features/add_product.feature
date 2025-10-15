Feature: Gestion de Inventario

  Scenario: Agregar un producto nuevo al inventario
    Given el inventario esta vacio
    When agrego un producto llamado "Leche" con precio "1.50" y stock "10"
    Then el producto "Leche" debe existir en el inventario con un stock de 10