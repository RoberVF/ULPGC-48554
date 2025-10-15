# SPRINT 5. DOXYGEN Y BDD CON BEHAT INSTAURADOS {#sprint5_page}

## Doxygen
Instaurar doxygen ha sido bastante sencillo y es cierto que le da un punto bastante mas formal al proyecto. 
Para ello he ejecutado:
```doxygen -g Doxyfile```

He realizado diferentes configuraciones en el archivo Doxyfile que se ha generado para que doxygen consiga "entender" 
mi proyecto y despues he ejecutado:
```doxygen Doxyfile```

Tras esto, se ha creado una carpeta html/ en la cual existe un archivo **index.html** que muestra toda la documentacion 
del proyecto.


## BDD CON BEHAT
En primer lugar comenzaremos incluyendo **behat** con composer en el proyecto:
```composer require --dev behat/behat```

Una vez instalado, para inicializarlo utilizare:
```./vendor/bin/behat --init```

Esto creara una carpeta en la raiz del proyecto llamada ```features/``` donde se crearan los archivos ```.feature``` los 
cuales seran los encargados de contener la informacion de los tests en lenguaje natural.
Por otro parte tenemos ```FeatureContext.php``` archivo que sera un puente entre el lenguaje Gherkin (el escrito en ```.feature```) y el codigo PHP.

Para correr cada uno de los archivos se utilizara la siguiente sentencia:
```./vendor/bin/behat features/add_product.feature```

Entonces, tras haber realizado ciertos tests concluyo que TDD con PHPUnit nos asegura que cada cosa funciona bien individualmente 
mientras que BDD con Behat nos asegura que el flujo de trabajo sea correcto.
