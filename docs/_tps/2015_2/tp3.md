---
title: Trabajo práctico n.º 3
cursada: 2015/2
deadline: 2015-12-04
---


Introducción
============

En un intento desesperado para ganar las elecciones nacionales de un desconocido país, uno de los candidatos decide embarcarse en un proyecto multimillonario: la creación de rutas ferroviarias que conecten toda la nación para poder ganar los votos de los ciudadanos más indecisos.

Sus asesores especializados en transporte (y marketing) recomendaron un listado de ciudades estratégicas con múltiples rutas para incluir en la planificación. Se conoce el largo de cada ruta, así como también la cantidad de gente favorecida con la creación de cada una. Sin embargo, como se cuenta con un presupuesto ajustado por encontrarse en los meses finales del año, no se pueden construir todas; sino que se deben construir las suficientes como para poder ganar el voto popular, interconectando todas las ciudades y maximizando la cantidad de gente beneficiada.

Para llevar a cabo este ambicioso proyecto se requiere de la previa renovación del tendido eléctrico de todas las ciudades. Se sabe que el costo de cada tramo es proporcional a la distancia entre las ciudades, y el único requerimiento es que exista una conexión entre todas para poder alimentar todo el circuito con un sólo generador dedicado.

Finalmente, como su contrincante político ya ha realizado un sistema que permite conocer la mejor ruta para trasladarse entre dos puntos de la ciudad capital del país, se requiere un sistema que además nos provea la posibilidad de conocer el recorrido mínimo (sobre las rutas construidas previamente) para ir de una determinada ciudad a otra, y exportarlo en un cómodo mapa.

Consigna
============

Dado un listado de ciudades y un listado de rutas que las conectan, implementar un programa que modele la situación descripta usando un grafo y que permita resolver los siguientes problemas:

- La selección de las rutas que conecten todas las ciudades maximizando la cantidad de gente favorecida y considerando el largo de cada ruta. Otros datos que se pueden tener en cuenta son la población de las ciudades a interconectar y la provincia a la que pertenecen.

  No es necesario que el resultado de la operación resulte en un árbol, sino que puede haber varios caminos que conecten dos ciudades.

  No existe un límite de rutas posibles a usar, pero sí es obligatorio justificar en el informe el criterio utilizado para hacer la selección de caminos.

- La selección de caminos entre ciudades para abastecer de energía eléctrica a todas las estaciones usando un árbol de tendido mínimo.

  Este árbol debe ser construido con un subconjunto de las rutas seleccionadas en el ítem anterior.

- La obtención de rutas eficientes entre dos ciudades y exportación a un mapa usando el formato KML.


Entrada
============

Se proveen dos archivos con información que deberá ser interpretada para realizar el trabajo práctico.

Archivo de ciudades
-------------------

Se trata de un archivo llamado [ciudades.csv] que cuenta con los registros de las ciudades, con la siguiente información:

- `id`: identificador unívoco de la ciudad, de tipo entero.
- `nombre`: nombre completo de la ciudad.
- `longitud`: coordenada de longitud de la ubicación geográfica de la ciudad, de tipo decimal.
- `latitud`: coordenada de latitud de la ubicación geográfica de la ciudad, de tipo decimal.
- `provincia`: número que indica la provincia en la que se encuentra la ciudad.
- `habitantes`: número que indica la cantidad de habitantes de la ciudad.

[ciudades.csv]: https://github.com/algoritmos-rw/tps41/blob/2015_2/tp3/ciudades.csv

Archivo de rutas
----------------

Se trata de un archivo llamado [rutas.csv] que cuenta con las posibles rutas a incluir para resolver el problema. Tiene la siguiente información:

- `id`: identificador unívoco de la ruta, de tipo entero.
- `id_ciudad_1`, `id_ciudad_2`: identificadores de las ciudades que son conectadas por la ruta, de tipo entero.
- `puntaje`: un número entero que representa la cantidad de gente que es favorecida por la creación de la ruta (mientras más alto, más gente es favorecida).
- `distancia`: un número decimal que indica el largo de la ruta, es decir, la distancia entre las dos ciudades que conecta.

[rutas.csv]: https://github.com/algoritmos-rw/tps41/blob/2015_2/tp3/rutas.csv

Comportamiento del programa
============

Al ser ejecutado, el programa deberá procesar los archivos de entradas de rutas y ciudades, y:

- Seleccionar las rutas a considerar de acuerdo a algún criterio justificado y exportar el mapa de la red en un archivo KML llamado `red.kml`.

- Seleccionar las rutas para establecer el tendido de energia eléctrica, y exportarlo en un archivo KML llamado `tendido.kml`.

Una vez realizado esto, la aplicación funcionará para encontrar una ruta eficiente entre dos ciudades usando los algoritmos vistos en clase. Para realizar esto le debe solicitar al usuario los identificadores de las ciudades por las que se desea trasladar.
El programa deberá generar un archivo KML llamado:

    ruta_{id_ciudad_1}_{id_ciudad_2}.kml

que contenga el mapa que muestre la ruta entre las ciudades.


Archivos KML
============

Los archivos KML son archivos de texto plano utilizados por aplicaciones como Google Earth o Google Maps para mostrar información geográfica. Estos archivos deben cumplir un estándar con el que se pueden representar puntos, líneas y polígonos, entre otras cosas.

La referencia completa de esta sintaxis está disponible en Internet ([link][1]). Sin embargo, aquí se definen un subconjunto mínimo de instrucciones para generar archivos KML con la información necesaria para visualizar las rutas.

Para visualizar estos archivos generados se puede usar [Google Maps][2] o alguna aplicación externa que no requiere haber iniciado sesión con una cuenta de Google (por ejemplo, [display-kml.appspot.com][3]).

Se incluye junto a este enunciado un archivo KML de ejemplo.

[1]: https://developers.google.com/kml/documentation/?hl=en
[2]: https://support.google.com/mymaps/answer/3024836?hl=en
[3]: http://display-kml.appspot.com/


Encabezado XML
--------------------

La primera línea de cada archivo KML debe ser el encabezado del estándar XML:

    <?xml version="1.0" encoding="UTF-8"?>

Declaración de KML (inicio)
--------------------

Las siguientes líneas del archivo indica que se trata de un archivo KML y se anuncia su inicio:

    <kml xmlns="http://earth.google.com/kml/2.1">
        <Document>

Información del archivo KML
--------------------

A continuación se puede agregar el nombre del archivo y una descripción.

    <name>KML de ejemplo</name>
    <description>Un ejemplo introductorio.</description>

Contenido geográfico
--------------------

El lenguaje incluye muchos componentes para visualizar en mapas, especificando su estilo y muchos atributos. Para el alcance de este trabajo sólo serán necesarios dos que serán explicados en esta sección.
Se pueden incluir muchos de estos componentes en un mismo archivo sin necesidad de ordenarlos ni especificar su cantidad previamente.


### Lugares ###

Se usan para indicar un lugar de interés en las coordenadas especificadas:

    <Placemark>
        <name>Facultad de Ingeniería, UBA</name>
        <Point>
            <coordinates>-58.3679593, -34.6176355</coordinates>
        </Point>
    </Placemark>

Este ejemplo ubica un punto con el nombre “Facultad de Ingeniería, UBA” en la coordenada indicada (especificando primero la longitud y luego la latitud, separadas por comas).


### Líneas ###

Se usan para indicar un recorrido entre las coordenadas especificadas:

    <Placemark>
        <LineString>
            <coordinates>-58.36795, -34.61763 -58.39644, -34.58850</coordinates>
        </LineString>
    </Placemark>

Este ejemplo dibuja una ruta entre los dos puntos indicados.


Declaración de KML (fin)
--------------------

Se indica el fin del archivo.

        </Document>
    </kml>


Criterios de aprobación
=======================

Los siguientes aspectos son condición necesaria para la aprobación del trabajo
práctico.

Estructuras de datos
--------------------

Para la realización de este trabajo es necesario utilizar la estructura de
datos **grafo** vista en clase, además de crear las estructuras adicionales que
se consideren necesarias.

Puede utilizar todas las estructuras de datos que se crean convenientes, así como
aplicar las técnicas de programación vistas en clase para resolver cada problema.

Todas las estructuras deben estar implementadas de la forma más genérica posible y
correctamente documentadas.

Código del programa
-------------------

El código entregado debe:

- ser claro y legible, y estar estructurado en funciones lo más genéricas
  posible, adecuadamente documentadas.

- compilar sin advertencias y correr sin errores de memoria.

- ajustarse a la especificación de la consigna y pasar todas las pruebas
  automáticas.


Informe
=======

El informe deberá consistir de las siguientes partes:

- carátula con los datos personales del grupo y el ayudante asignado.

- análisis y diseño de la solución, en particular: algoritmos y estructuras de
  datos utilizados, y por qué. Orden de ejecución de cada etapa del programa.

- implementación: incluir todo el código fuente utilizado (en formato
  `monoespaciado`, para facilitar su lectura).


Entrega
=======

El trabajo a entregar consiste en:

- el informe impreso.

- el informe en formato `.pdf`. Para el código fuente utilizar una tipografía
  `monoespacio`.

- una copia de todo el código fuente, en un archivo `.zip`.

Los dos últimos deben enviarse a la dirección `tps.7541rw@gmail.com`, colocando
como asunto:

        TP3 - Padrón 1 - Apellido 1 - Padrón 2 - Apellido 2

Este trabajo práctico se desarrolla en forma grupal. El informe impreso debe
entregarse en clase. El plazo de entrega vence el **viernes 4 de diciembre de
2015**.
