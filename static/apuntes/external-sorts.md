---
layout: default
title: Algoritmos de Ordenamiento Externo
permalink: /apuntes/ordenamiento_externo
math: true
---

# Algoritmos de Ordenamientos Externos

Llamamos ordenamiento externo cuando debemos ordenar archivos que son (mucho) más grandes de lo que nuestra memoria puede llegar a abarcar. Esto es así porque, en caso contrario, podríamos simplemente cargar el archivo en memoria y ordenarlo usando cualquier algoritmo de ordenamiento convencional. 

Hoy en día es raro necesitar utilizar algoritmos como estos debido a que contamos con mucha más memoria RAM de lo que se hacía una década atrás. 
Este era un tema que hasta hace unos años se daba en la materia _Organización de Datos_, pero dado que poco tenía que ver con el resto del temario, y que tiene más sentido en nuestra materia, decidieron dejar de darlo. 

Supongamos entonces que contamos con un caso así. Estamos queriendo ordenar un archivo completamente desordenado, bajo algún criterio que no es importante. El algoritmo que podríamos utilizar podría hacer algo como:
1. Generar _k_ particiones ordenadas. Una partición de un archivo es un sub-archivo, donde todos juntos tienen todas las líneas ó registros del archivo original, sin repeticiones. Cada archivo tendrá $$n_i$$ (_i_ entre 0 y _k-1_) registros, donde la suma de todos los $$n_i$$ será _n_, la cantidad total de registros del archivo original. 
2. Juntar las _k_ particiones ordenadas en un nuevo archivo ordenado. Esto sería una generalización del _intercalar ordenado_ de mergesort. 

Por lo tanto, la idea es: separamos el archivo original en _k_ particiones. Cada una de esas particiones nos aseguraremos que estén ordenadas, y luego uniremos las particiones en un archivo final, ordenado. 

Veremos cómo podemos implementar cada una de esas partes. Empezaremos por la segunda, que es la más sencilla.

## Juntar _k_ archivos ordenados

Esto en sí ya no necesariamente aplica para archivos, podría tranquilamente ser para arreglos (solo que en el caso de archivos, iremos leyendo del archivo en vez de un arreglo). La idea va a ser reutilizar el heap. Así como tenemos la opción de utilizar un heap para obtener los _k_ registros más grandes de un arreglo de _n_ registros en _O(n log k)_, también podemos hacer el merge de _k_ archivos (o arreglos) **ordenados** que tienen en total _n_ registros, en _O(n log k)_.

Así como es el caso del otro algoritmo, que el orden sea logarítmico sobre _k_ implica que en nuestro heap no tendremos nunca más de _k_ registros. Pero recordemos que _k_ es la cantidad de archivos que tenemos. La idea es aprovechar el ordenamiento que tiene los archivos desde el inicio. 

El primer registro en cada archivo es el menor de todos los registros dentro de cada uno de ellos. Digamos, en el primer archivo el primer registro es el más chico entre todos los registros del primer archivo (o a lo sumo, igual).

Eso quiere decir, que el menor entre todos los _K_ primeros va a ser el menor de todos los _n_ registros. Por lo tanto, va a ser el primer registro, sí o sí, del archivo (o archivo) final. Ahora tenemos que ver cuál va a ser el segundo. Pero, ¿no es posible que el segundo registro sea también proveniente del archivo del que vino el más chico que sacamos antes? Por ejemplo, si tenemos los archivos [0, 1, 2] y [2, 3, 4], los dos registros más chicos vienen del primer archivo. Entonces, tenemos que conseguir siempre comprar _k_ registros, uno de cada archivo. Pero cuando sacamos uno, entonces quedarnos con _su sucesor_. Ya sabiendo que vamos a comparar _k_ cosas, podemos usar el heap de manera similar:
1. Creamos un heap de minimos (o de máximos con función de comparación alternada).
2. Guardamos el primer registro de cada archivo. _Importante_: vamos a necesitar poder reconstruir de dónde vino ese registro, por lo que no se puede encolar así nada más. Será necesario crear una estructura ad-hoc solamente para este fin, y guardar: el registro en si y el número de archivo del que vino. La función de comparación solo debe tener en cuenta lo primero. 
3. Sacamos un registro del heap, que sabemos será el menor de todos, por lo que será el primer registro de nuestro archivo final (por lo que directamente deberíamos escribirlo).
4. Agarramos el siguiente registro del archivo del cual provino ese registro anterior (simplemente lo leemos), y lo guardamos en el heap. Si el archivo ya fue leido completamente, salteamos esto porque ya terminamos de procesarlo. A partir de ese momento, el heap tendrá un registro menos.  
5. Si el heap aun tiene registros, volvemos al paso 3. Sino, entonces el algoritmo termina y ya tenemos nuestro archivo ordenado. 

Dado que se hacen _n_ encolar y desencolar en un heap que siempre tiene a lo sumo _k_ registros, cada operación es _O(log k)_, al ser _n_ las veces que se hace: _O(n log k)_.

## Generar particiones ordenadas

Veremos 3 implementaciones para esto. Una particularidad: el valor de _n_ no puede cambiar (depende del archivo original), pero si podemos ver de manejar el valor de _k_. Cuanto menor cantidad de particiones ordenadas genermos, menor costo tendremos a la hora de hacer el merge ordenado explicado arriba. 


Para los 3 algoritmos propuestos vamos a suponer que tenemos una cota _C_ de elemenos máximos que podemos tener en memoria. Nunca podemos tener más de _C_ registros en memoria. El valor de _C_ óptimo será cuestión de experimentación, o de poner un valor razonable. 

### Opcion 1: Ordenamientos internos
1. Cargar _C_ registros en memoria (por ejemplo, en un arreglo), y ordenarlos con algún algoritmo eficiente. 
2. Escribir el arreglo ordenado en un archivo (partición).
3. Repetir lo anterior hasta terminar el archivo original. 

Este algoritmo permite crear particiones de tamaño _C_, por lo que tendremos _n/C_ particiones. 

### Opcion 2: Replacement-Selection sort
1. Crear un heap de mínimos, y una lista (podría ser otra estructura similar).
2. Poner _C_ registros del archivo en el heap. Así, el heap quedará _lleno_.
3. Escribir en el archivo el primer registro del heap (el menor dentro del heap). Con eso, tendremos lugar para guardar un registro más en el heap.
4. Leemos un nuevo registro del archivo original. 
5. Si el registro que acabamos de leer es mayor o igual al que acabábamos de sacar, simplemente lo encolamos sin más.
6. Si en cambio, el registro fuera menor que el que sacamos antes, lo guardamos en la lista (lo veremos más adelante). De esta manera, nuestro heap tendrá un registro menos.  
7. Si aún quedan registros en el heap, volvemos al paso 3. Si no quedan más registros, cerramos la partición actual, y creamos otra. Pasamos todos los registros de la lista al heap (que debería tener _C_ registros). Podemos hacer esto creando el heap desde un arreglo para que sea en _O(n)_. Volvemos al paso 2. 

Si en cualquier momento el archivo ya no tiene más registros, simplemente obviamos la acción de guardar un nuevo registro en el heap. 

Este algoritmo permite tener particiones de, en promedio, _2C_ registros, teniendo en total _n/2C_ particiones. 

[Aquí](https://www.youtube.com/watch?v=m0v-trXc2yI) un video donde se hace un seguimiento del algoritmo. 

### Opción 3: Natural-Selection sort

Similar al anterior, pero en vez de guardar los archivos en una lista, los guardamos en disco, y nos aseguramos de guardar hasta _C_ registros en ese archivo temporal (y volvemos a leer del archivo, hasta que nos topemos con uno mayor o igual, o tengamos _C_ registros en el archivo temporal). Al escribirlos en disco, permitimos que el heap siga pudiendo guardar registros. Cuando llegamos a _C_ registros en el archivo, simplemente escribimos todo el heap en la partición que estábamos armando, y cargamos los registros del archivo temporal. 

Antes, al toparnos con que teníamos _C_ registros en la lista, no teníamos nada para guardar, pero ahora vamos a tener _C_ registros (los que quedaron en el heap, que siempre va a tener _C_ registros, salvo en el caso final que tendrá uno menos). Entonces, en vez de generar particiones de _2C_, las genera de tamaño _3C_, teniendo entonces _n/3C_ particiones. La contra en este caso es tener que cargar los registros del archivo temporal provenientes de disco. 


### Costo de generar las particiones

En cualquiera de los casos, notar que siempre estaremos trabajando con un heap con _C_ registros, y de alguna forma u otra guardaremos todos los registros en el heap, por lo tanto, el orden de realizar estas operaciones es _O(n log c)_. 

## Costo Total

Teniendo que _k_ valdrá _O(n/C)_ (con alguna constante dividiendo: 1, 2 o 3), tendrémos que nuestro algoritmo finalmente será: 

	SortExterno(n) = O(particiones ordenadas) + O(merge)
	SortExterno(n) = O(n log c) + O(n log n/c) = O(n log c) + O(n log n) - O(n log c) = O(n log n)

Con eso comprobamos que, lógicamente, nuestro algoritmo ordena en _O(n log n)_. Ahora bien: ¿por qué deberíamos darle importancia si generamos más o menos particiones, si a cuestiones del orden no nos importa? Primero, porque a grandes rasgos es una buena optimización, que se escapa del análisis del orden del algoritmo planteado por la notación _Big Oh_. Pero más importante: estamos hablando de operaciones de lectura y escritura sobre disco. Dichas operaciones toman más tiempo que muchas otras operaciones (si bien ese tiempo sigue siendo constante, es muy grande). Por esto, es que planteamos como posibles mejoras tanto Replacement Selection como Natural Selection. 

## Recomendaciones

A la hora de trabajar con accesos a disco, es importante tener en cuenta que a menos que trabajen con un disco de estado solido (SDD), leer seguido puede ser una operación (muy) costosa, y lo mismo al escribir. 
Pueden utilizar tanto getline como cualquier otra función ya vista, pero recomendamos:
* Para lecturas: no usar getline, sino algo que les permita leer directamente una mayor cantidad de bytes de un solo acceso a disco¸usando fread. Tendrán que tener en cuenta que tendrán que separar ustedes por los `\n` (sencillo utilizando el `split` ya implementado, y mucho más veloz por utilizar accesos a memoria volátil). ¡Cuidado! Recuerden que la _última linea_ podría haber quedado incompleta al leer del archivo.
* Para escrituras, hacer algún tipo de buffer. Pueden por ejemplo guardar en una lista o cola _n_ líneas (fijado por ustedes), luego unirlas (utilizando `join`), y finalmente escribirlas a disco. 

En caso que se trate de un archivo binario, cuyos registros son de tamaño fijo, esta operación se hace mucho más sencillo, puesto que fread y fwrite ya pueden funcionar perfectamente con arreglos de estructuras.

