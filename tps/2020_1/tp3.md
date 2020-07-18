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
    $ ./netstats Wiki_parsed.txt
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
1. Se deben conseguir al menos 10 puntos para poder aprobar el TP.
1. En caso de obtener menos de 12 puntos, la nota máxima será 9.
1. En caso de obtener 14 puntos o más la nota máxima del trabajo práctico puede llegar a 11.
1. El total de puntos entre todas las funcionalidades es 16.

#### Listar operaciones (obligatorio, sin puntos)

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

#### Camino más corto (★)

* Comando: `camino`
* Parámetros: `origen` y `destino`. Origen y destino son **páginas**.
* Utilidad: nos imprime una lista con las **páginas** con los cuales navegamos de la página `origen` a la página `destino`, navegando lo menos posible.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(P + L)$$, siendo $$P$$ la cantidad
de páginas, y $$L$$ la cantidad de Links en toda la red.
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

#### Artículos más importantes (★★★)

Utlizaremos el algoritmo de [PageRank](/algo2/material/apuntes/pagerank) para implementar este comando,
dado que además fue pensado primordialmente para este escenario.

* Comando: `mas_importantes`
* Parámetros: `n`, la cantidad de páginas más importantes a mostrar.
* Utilidad: nos muestra las `n` páginas más centrales/importantes del mundo según el algoritmo de
pagerank, de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(K(P + L) + P \log (n))$$, siendo $$K$$ la cantidad de
iteraciones a realizar para llegar a la convergencia (puede simplificarse a $$\mathcal{O}(P \log n + L)$
(El término $$\mathcal{O}(P \log n)$$ proviene de obtener los Top-n luego de haber aplicado el algoritmo).
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

#### Conectividad (★★)

* Comando: `conectados`
* Parámetros: `página`, la página al que se le quiere obtener la conectividad.
* Utilidad: nos muestra todos las páginas a los que podemos llegar desde la `página` pasado por parámetro y que, a su vez, puedan también volver a dicha `página`.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(P + L)$$. Considerar además que a todas las páginas a las que lleguemos también se conectan entre sí, y con el tamaño del set de datos puede convenir guardar los resultados. 


#### Ciclo de n artículos (★★★)

* Comando: `ciclo`
* Parámetros: `página` y `n`.
* Utilidad: permite obtener un ciclo de largo `n` que comience en la página indicada. 
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(P^n)$$, pero realizando una buena poda puede reducirse
sustancialmente el tiempo de ejecución.


#### Lector a las 2 a.m. (★★)

* Comando: `lector`
* Parámetros: `página1`, `página2`, ..., `página_n`.
* Utilidad: Permite obtener un orden en el que es válido leer las páginas indicados. Para que un orden sea válido, si `página_i` tiene un link a `página_j`, entonces es necesario **primero leer** `página_j`. Solo se debe tener en cuenta los artículos mencionados en los parámetros. Esto, por supuesto, puede implicar que no podamos cumplir con lo pedido por encontrarnos con un ciclo.   
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(n + L_n)$$, siendo $$n$$ la cantidad de páginas indicadas, y $$L_n$$ la cantidad de links entre estas. 

**Importante**: considerar lo indicado en el enunciado. Si quiero saber un orden válido para leer `página1` y `página2`, y hay un link de `página1` a `página2`, un orden válido es `página2` y luego `página1`. 

#### Diametro (★)

* Comando: `diametro`
* Parámetros: ninguno. 
* Utilidad: permite obtener el diámetro de toda la red. Esto es, obtener el largo de camino mínimo más grande de toda la red. 
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(P(P + L))$$.

#### Todos en Rango (★)

* Comando: `rango`
* Parámetros: `página` y `n`. 
* Utilidad: permite obtener todos las páginas que se encuenten a exactamente `n` links/saltos desde la `página` pasada por parámetro.  
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(P + L)$$.

#### Comunidades (★★)

* Comando: `comunidades`. 
* Parámetros: `página`. 
* Utilidad: permite obtener la comunidad dentro de la red a la que pertenezca la página pasada por parámetro. Para esto, utilizaremos el sencillo algoritmo de [Label Propagation](/algo2/material/apuntes/label_propagation).

#### Navegacion por primer link (★)

* Comando: `navegación`. 
* Parámetros: `origen`, `destino` y n. 
* Utilidad: Se dice que si comenzamos en _cualquier_ artículo de wikipedia, y navegamos únicamente utilizando el primer link, eventualmente llegaremos al artículo de _Filosofía_. Por tanto, queremos implementar un comando que navegue usando el primer link (de los que tengamos reportados) desde la página `origen` y verificar si podemos llegar a la página `destino` en a lo sumo de `n` pasos.  
* Complejidad: este comando debe ejecutar en $$\mathcal{O}(n)$$.


## Entrega

Adicionalmente a los archivos propios del trabajo práctico debe agregarse un archivo `entrega.mk` que contenga la regla `netstats` para generar el ejecutable de dicho programa (sea compilando o los comandos que fueren necesarios). Por ejemplo, teniendo un TP elaborado en Python, podría ser:

``` makefile
netstats: netstats.py grafo.py biblioteca.py
    cp netstats.py netstats
    chmod +x netstats
```

**Importante**: En caso de recibir un error `FileNotFoundError: [Errno 2] No such file or directory: './netstats': './netstats'`, tener en cuenta que para el caso de enviar código escrito en Python es necesario además indicar la ruta del intérprete. Esto puede hacerse agregando como primera línea del archivo principal (en el ejemplo, sería `netstats.py`) la línea: `#!/usr/bin/python3`.

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código del TDA Grafo programado, y cualquier otro TDA que fuere necesario.
- el código de la solución del TP.

La entrega se realiza en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.
