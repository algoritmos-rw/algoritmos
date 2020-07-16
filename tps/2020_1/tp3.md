---
math: true
---

{% assign tp = site.data.trabajos.TP3 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

Trabajo Práctico 3
================
{:.no_toc}

El trabajo práctico número 3 tiene fecha de entrega para el día **{{fecha}}**.

## Contenido
{:.no_toc}

* Contenido
{:toc}


## Introducción

(METER BARDO A AGUAD?)

El objetivo de este trabajo práctico es el de modelar Internet: las páginas web y sus interacciones. 
Nos interesa modelar cómo podemos navegar a través de Internet. Sobre esto, quieren poder realizarse varias
consultas para poder entender distintos aspectos de la red. Particularmente, nosotros trabajaremos con porciones
ínfimas de la red.


## Datos disponibles

Vamos a trabajar con una ínfima porción de Internet, del portal llamado "Wikipedia". Es posible descargarse el contenido completo de Wikipedia en cualquier idioma desde [aquí](https://dumps.wikimedia.org/backup-index.html). Nosotros nos enfocaremos en la versión en español, si bien el trabajo es completamente compatible con cualquier otro idioma, pero el dump en idioma inglés es mucho más pesado.

Además, les brindamos a ustedes [un parser implementado en Python](https://drive.google.com/file/d/0B_oxuLrlET2hMmx3N0dGR2dNMWc/view?usp=sharing) para que no sea necesario que ustedes lo implementen. En caso de preferir implementar algún cambio sobre el mismo, o utilizar uno propio, no hay inconvenientes. Igualmente, para que no sea necesario consumir tiempo en esta tarea se brinda [un archivo de texto de salida ya parseado](https://drive.google.com/file/d/0B_oxuLrlET2heURHOFlKUFo1WXc/view?usp=sharing), que una vez descomprimido pesa 1.1GB. Dicho archivo proviene del dump de Wikipedia en español hasta el día 1/5/2016, pero ya es posible descargar versiones más actualizadas, o bien de otras wikis.
En caso de no utilizar ese archivo, o simplemente para experimentar (con otro idioma, por ejemplo) pueden simplemente ejecutarlo haciendo:
```
    $ python wiki_parser.py <path_dump> <path_parsed>
```

El archivo parseado tiene el formato:
```
TituloArticulo1>Link1<Link2<Link3<...<LinkN
TituloArticulo2>Link1<Link2<Link3<...<LinkM
...
```

Dichos links deben hacer referencia a otros Títulos de Artículos. Tener en cuenta que, por simpleza del parser, pueden haber links que referencien a artículos que no existan. Por ejemplo: se han filtrado las entradas de artículos referentes a años, para hacer más liviano el archivo y más interesantes los caminos a recorrer por nuestra "Pequeña Internet".

Considerar que el archivo completo cuenta con más de 3 millones de artículos. Por lo tanto, para que puedan también realizar pruebas más rápidas, les brindamos un archivo de [una wiki más pequeña](LINK), así como [una reducción de la primera red](LINK) que cuenta con 100.00 artículos. 

## Consigna

Dado este archivo parseado, se debe modelar Internet con una estructura Grafo, considerando únicamente los títulos de las páginas y las conexiones entre ellas. Esto implica determinar todas las características necesarias para el grafo. 
Se pide implementar un programa que cargue inicialmente el grafo, y que reciba como parámetros la ruta del archivo parseado:
```
    $ ./tp3 Wiki_parsed.txt
```

Una vez cargada la red, se deberán realizar acciones sobre la misma, a partir de comandos ingresados desde entrada estándar. 

### Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Python y C, y cualquier otro a ser discutido con el corrector asignado.

El trabajo consiste de 3 partes:
1. El TDA Grafo, con sus primitivas, completamente agnósticas sobre su uso para modelar la red de Internet.  
1. Una biblioteca de funciones de grafos, que permitan hacer distintas operaciones sobre un grafo que modela Internet, sin importar cuál es la red específica.
1. El programa `NetStats` que utilice tanto el TDA como la biblioteca para poder implementar todo
lo requerido.

El programa debe recibir por parámetro y cargar en memoria el set de datos (`$ ./netstats
Wiki_parsed.txt`) y luego solicitar el ingreso de comandos por entrada estándar,
del estilo `<comando> 'parametro'`. Notar que esto permite tener un archivo de instrucciones a ser
ejecutadas (i.e. `$ ./netstats Wiki_parsed.txt < entrada.txt`).

De todas las funcionalidades, pueden optar por implementar distintas. Algunas consideraciones:
1. Cada funcionalidad e implementación otorga distinta cantidad de puntos, basado en dificultad y
el interés del curso en que implementen dicha funcionalidad o implementación
particular de la misma (Cada estrella ★ corresponde a un punto).
1. Se deben conseguir al menos 8 puntos para poder aprobar el TP.
1. En caso de obtener menos de 10 puntos, la nota máxima será 9.
1. En caso de obtener 14 puntos o más la nota máxima del trabajo práctico puede llegar a 11.
1. El total de puntos entre todas las funcionalidades es 16.

### Listar operaciones (obligatorio, sin puntos)

* Comando: `listar_operaciones`.
* Parámetros: ninguno.
* Utilidad: Dado que no todas las funcionalidades o implementaciones son obligatorias, debe
existir un comando que nos permita saber cuáles son las funcionalidades disponibles. Debe
imprimirse una línea por cada **comando** que esté implementado.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(1)$$.
* Ejemplo:
Entrada:
    ```
    listar_operaciones
    ```
Salida:
    ```
    camino
    mas_importantes
    conectados
    ciclo
    en_rango
    ```

### Camino más corto (★)

* Comando: `camino`
* Parámetros: `origen` y `destino`. Origen y destino son **artículos**.
* Utilidad: nos imprime una lista con los **artículos** con los cuales navegamos del
artículo `origen` al artículos `destino`, navegando lo menos posible.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A + L)$$, siendo $$A$$ la cantidad
de artículos, y $$L$$ la cantidad de Links en toda la red.
* Ejemplo:
Entrada:
    ```
    camino Argentina,Zinedine Zidane
    camino (poner otro ejemplo)
    ```
Salida:
    ```
    Argentina -> Copa Mundial de Fútbol -> Zinedine Zidane
    (...)
    ```

### Artículos más importantes (★★★)

Utlizaremos el algoritmo de [PageRank](/algo2/material/apuntes/pagerank) para implementar este comando,
dado que además fue pensado primordialmente para este escenario.

* Comando: `mas_importantes`
* Parámetros: `n`, la cantidad de artículos más importantes a mostrar.
* Utilidad: nos muestra los `n` artículos más centrales/importantes del mundo según el algoritmo de
pagerank, de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(K(A + L) + A \log (n))$$, siendo $$K$$ la cantidad de
iteraciones a realizar para llegar a la convergencia (puede simplificarse a $$\mathcal{O}(A \log n + L)$
(El término $$\mathcal{O}(A \log n)$$ proviene de obtener los Top-n luego de haber aplicado el algoritmo).
Entrada:
    ```
    mas_importantes 5
    ```
Salida:
    ```
    ...
    ```

**Importante**: Considerar que esto podría pedirse varias veces por ejecución, pero que los elementos van
a ser igual de importantes en cada ejecución.

### Conectividad (★★)

CFC


### Viaje de N lugares (★★★)

Ciclo largo n


### Lector a las 2 a.m. (★★)

Orden topologico

### Diametro (★)

### Todos en Rango (★)

### Comunidades (★★)

### Navegacion por primer link (★)


## Criterios de aprobación


### Código del programa

El código entregado debe:

- ser claro y legible, y estar estructurado en funciones lo más genéricas
  posible, adecuadamente documentadas.

- compilar sin advertencias y correr sin errores de memoria.

- ajustarse a la especificación de la consigna y pasar todas las pruebas
  automáticas.

### Entrega

La entrega incluye, obligatoriamente, los siguientes archivos:

- El código de los TDAs utilizados.
- El código del TP.
- Un archivo _deps.mk_ que exprese las dependencias del proyecto en formato
    makefile. Este archivo deberá contener solamente dos líneas que indiquen,
    para cada programa, de qué _objetos_ depende su ejecutable; por ejemplo:

    ```
    # Ejemplo de archivo deps.mk para el TP2
    zyxcba: zyxcba.o csv.o hash.o
    ```

La entrega se realiza exclusivamnete en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.
