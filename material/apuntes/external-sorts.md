---
permalink: /material/apuntes/ordenamientos_externos/
math: true
---

# Algoritmos de Ordenamientos Externos

Llamamos ordenamiento externo cuando debemos ordenar archivos que son (mucho) más grandes de lo que nuestra memoria puede llegar a abarcar. Esto es así porque, en caso contrario, podríamos simplemente cargar el archivo en memoria y ordenarlo usando cualquier algoritmo de ordenamiento convencional.

Supongamos entonces que contamos con un caso así. Estamos queriendo ordenar un archivo completamente desordenado, bajo algún criterio que no es importante. El algoritmo que podríamos utilizar podría hacer algo como:
1. Generar $$k$$ particiones ordenadas. Una partición de un archivo es un sub-archivo, donde todos juntos tienen todas las líneas ó registros del archivo original, sin repeticiones. Cada archivo tendrá $$n_i$$ registros (con $$i$$ entre $$0$$ y $$k-1$$), donde la suma de todos los $$n_i$$ será $$n$$, la cantidad total de registros del archivo original.
2. Juntar las $$k$$ particiones ordenadas en un nuevo archivo ordenado. Esto sería una generalización del _intercalar ordenado_ de mergesort.

En resumen, la idea es: separamos el archivo original en $$k$$ particiones. Cada una de esas particiones nos aseguraremos que queden ordenadas, y luego uniremos las particiones en un archivo final ordenado, aprovechando que las particiones quedaron ordenadas.

Veremos cómo podemos implementar cada una de esas partes. Empezaremos por la segunda, que es la más sencilla.

## Juntar $$k$$ archivos ordenados

Esto en sí ya no necesariamente aplica para archivos, podría tranquilamente ser para arreglos (solo que en el caso de archivos, iremos leyendo del archivo en vez de un arreglo). La idea va a ser reutilizar el heap. Así como tenemos la opción de utilizar un heap para obtener los _k_ registros más grandes de un arreglo de $$n$$ registros en $$\mathcal{O}(n \log k)$$, también podemos hacer el merge de $$k$$ archivos (o arreglos) **ordenados** que tienen en total $$n$$ registros, en $$\mathcal{O}(n \log k)$$.

Así como es el caso del algoritmo de _top-k_, que el orden sea logarítmico sobre $$k$$ implica que en nuestro heap no tendremos nunca más de $$k$$ registros. Pero recordemos que $$k$$ es la cantidad de archivos que tenemos. La idea es aprovechar el ordenamiento que tienen los archivos desde el inicio.

El primer registro en cada archivo es el menor de todos los registros dentro de cada uno de ellos. Digamos, en el primer archivo el primer registro es el más chico entre todos los registros del primer archivo (o a lo sumo, igual).

Eso quiere decir, que el menor entre todos los $$k$$ primeros va a ser el menor de todos los $$n$$ registros. Por lo tanto, va a ser el primer registro, sí o sí, del archivo (o arreglo) final. Ahora tenemos que ver cuál va a ser el segundo. Pero, ¿no es posible que el segundo registro sea también proveniente del archivo del que vino el más chico que sacamos antes? Por ejemplo, si tenemos los archivos [0, 1, 2] y [2, 3, 4], los dos registros más chicos vienen del primer archivo. Entonces, tenemos que conseguir siempre comparar $$k$$ registros, uno de cada archivo. Pero cuando sacamos uno, entonces quedarnos con _su sucesor_. Ya sabiendo que vamos a comparar $$k$$ cosas, podemos usar el heap de manera similar:

1. Creamos un heap de minimos (o de máximos con función de comparación alternada).
2. Guardamos el primer registro de cada archivo. _Importante_: vamos a necesitar poder reconstruir de dónde vino ese registro, por lo que no se puede encolar así nada más. Será necesario crear una estructura ad-hoc solamente para este fin, y guardar: el registro en si y el número de archivo del que vino. La función de comparación solo debe tener en cuenta lo primero.
3. Sacamos un registro del heap, que sabemos será el menor de todos, por lo que será el primer registro de nuestro archivo final (por lo que directamente deberíamos escribirlo).
4. Agarramos el siguiente registro del archivo del cual provino ese registro anterior (simplemente lo leemos), y lo guardamos en el heap. Si el archivo ya fue leido completamente, salteamos esto porque ya terminamos de procesarlo. A partir de ese momento, el heap tendrá un registro menos.
5. Si el heap aún tiene registros, volvemos al paso 3. Sino, entonces el algoritmo termina y ya tenemos nuestro archivo ordenado.

Dado que se hacen $$n$$ encolar y desencolar en un heap que siempre tiene a lo sumo $$k$$ registros, cada operación es $$\mathcal{O}(\log k)$$, al ser $$n$$ las veces que se hace: $$\mathcal{O}(n \log k)$$.

**Aclaración**: Es importante eliminar los archivos temporales una vez terminada la operación de merge.

## Generar particiones ordenadas

Veremos 3 implementaciones para esto. Una particularidad: el valor de $$n$$ no puede cambiar (depende del archivo original), pero si podemos ver de manejar el valor de $$k$$. Cuanto menor cantidad de particiones ordenadas generemos, menor costo tendremos a la hora de hacer el merge ordenado explicado arriba.

Para los 3 algoritmos propuestos vamos a suponer que tenemos una cota $$C$$ de elemenos máximos que podemos tener en memoria. Nunca podemos tener más de $$C$$ registros en memoria. El valor de $$C$$ óptimo será cuestión de experimentación, o de poner un valor razonable.

### Opcion 1: Ordenamientos internos

1. Cargar $$C$$ registros en memoria (por ejemplo, en un arreglo), y ordenarlos con algún algoritmo eficiente.
2. Escribir el arreglo ordenado en un archivo (partición).
3. Repetir lo anterior hasta terminar el archivo original.

Este algoritmo permite crear particiones de tamaño $$C$$, por lo que tendremos $$\frac{n}{C}$$ particiones.

### Opcion 2: Replacement-Selection sort

1. Crear un heap de mínimos, y una lista (podría ser otra estructura similar).
2. Poner $$C$$ registros del archivo en el heap. Así, el heap quedará _lleno_.
3. Escribir en el archivo el primer registro del heap (el menor dentro del heap). Con eso, tendremos lugar para guardar un registro más en el heap.
4. Leemos un nuevo registro del archivo original.
5. Si el registro que acabamos de leer es mayor o igual al que acabábamos de sacar, simplemente lo encolamos sin más.
6. Si en cambio, el registro fuera menor que el que sacamos antes, lo guardamos en la lista (lo veremos más adelante). De esta manera, nuestro heap tendrá un registro menos.
7. Si aún quedan registros en el heap, volvemos al paso 3. Si no quedan más registros, cerramos la partición actual, y creamos otra. Pasamos todos los registros de la lista al heap (que debería tener $$C$$ registros). Podemos hacer esto creando el heap desde un arreglo para que sea en $$\mathcal{O}(n)$$. Volvemos al paso 2.

Si en cualquier momento el archivo ya no tiene más registros, simplemente obviamos la acción de guardar un nuevo registro en el heap.

Este algoritmo permite tener particiones de, en promedio, $$2C$$ registros, teniendo en total $$\frac{n}{2C}$$ particiones.

[Aquí](https://www.youtube.com/watch?v=m0v-trXc2yI) un video donde se hace un seguimiento del algoritmo.

### Opción 3: Natural-Selection sort

Similar al anterior, pero en vez de guardar los archivos en una lista, los guardamos en disco, y nos aseguramos de guardar hasta $$C$$ registros en ese archivo temporal (y volvemos a leer del archivo, hasta que nos topemos con uno mayor o igual, o tengamos $$C$$ registros en el archivo temporal). Al escribirlos en disco, permitimos que el heap siga pudiendo guardar registros. Cuando llegamos a $$C$$ registros en el archivo, simplemente escribimos todo el heap en la partición que estábamos armando, y cargamos los registros del archivo temporal.

Antes, al toparnos con que teníamos $$C$$ registros en la lista, no teníamos nada para guardar, pero ahora vamos a tener $$C$$ registros (los que quedaron en el heap, que siempre va a tener $$C$$ registros, salvo en el caso final que tendrá uno menos). Entonces, en vez de generar particiones de $$2C$$, las genera de tamaño $$3C$$, teniendo entonces $$\frac{n}{3C}$$ particiones. La contra en este caso es tener que cargar los registros del archivo temporal provenientes de disco.

### Costo de generar las particiones

En cualquiera de los casos, notar que siempre estaremos trabajando con un heap con $$C$$ registros, y de alguna forma u otra guardaremos todos los registros en el heap, por lo tanto, el orden de realizar estas operaciones es $$\mathcal{O}(n \log c)$$.

## Costo Total

Teniendo que $$k$$ valdrá $$\mathcal{O}(\frac{n}{C})$$ (con alguna constante dividiendo: 1, 2 o 3), tendrémos que nuestro algoritmo finalmente será:

$$
\begin{aligned}
\text{SortExterno}(n) &= \mathcal{O}(\text{particiones ordenadas}) +
\mathcal{O}(\text{merge}) \\

\text{SortExterno}(n) &= \mathcal{O}(n \log C) + \mathcal{O}(n \log \frac{n}{C}) \\

\text{SortExterno}(n) &= \mathcal{O}(n \log C) + \mathcal{O}(n \log n) -
\mathcal{O}(n \log C) = \mathcal{O}(n \log n)
\end{aligned}
$$

Con eso comprobamos que, lógicamente, nuestro algoritmo ordena en $$\mathcal{O}(n \log n)$$. Ahora bien: ¿por qué deberíamos darle importancia si generamos más o menos particiones, si a cuestiones del orden no nos importa? Primero, porque a grandes rasgos es una buena optimización, que se escapa del análisis del orden del algoritmo planteado por la notación _Big Oh_. Pero más importante: estamos hablando de operaciones de lectura y escritura sobre disco. Dichas operaciones toman más tiempo que muchas otras operaciones (si bien ese tiempo sigue siendo constante, es muy grande). Por esto, es que planteamos como posibles mejoras tanto Replacement Selection como Natural Selection.

## Recomendaciones

En caso de estar trabajando con líneas de texto (i.e. registros de longitud variable), una opción es buscar el máximo tamaño que puede llegar a ocupar una de estas líneas (llamémoslo M). Si tenemos a nuestra disposición _X_ KB de memoria, simplemente tendremos lugar para _X / M_ líneas. Entonces diremos que nuestro $$C$$ vale _X / M_. Esta es una buena forma de trabajar al principio, para simplificar. Una vez que se tenga el código funcionando, se puede mejorar (mucho) calculando en todo momento cuántos bytes estamos leyendo e incluso cuántos fuimos escribiendo. Esto último permite reducir mucho la cantidad de particiones.

A la hora de trabajar con accesos a disco, es importante tener en cuenta que aún trabajando con un disco de estado solido (SSD), leer de disco seguido puede ser una operación (muy) costosa, y lo mismo al escribir.
Pueden utilizar tanto `getline` como cualquier otra función ya vista, pero recomendamos:
* Para lecturas: no usar `getline`, sino algo que les permita leer directamente una mayor cantidad de bytes de un solo acceso a disco¸usando fread. Tendrán que tener en cuenta que tendrán que separar ustedes por los `\n` (sencillo utilizando el `split` ya implementado, y mucho más veloz por utilizar accesos a memoria volátil). ¡Cuidado! Recuerden que la _última linea_ podría haber quedado incompleta al leer del archivo.
* Para escrituras, hacer algún tipo de buffer. Pueden por ejemplo guardar en una lista o cola $$n$$ líneas (fijado por ustedes), luego unirlas (utilizando `join`), y finalmente escribirlas a disco.

En caso que se trate de un archivo binario, cuyos registros son de tamaño fijo, esta operación se hace mucho más sencilla, puesto que fread y fwrite ya pueden funcionar perfectamente con arreglos de estructuras.

## Preguntas adicionales

* ¿Qué sucedería si el archivo es tan, pero tan grande, que la cantidad de particiones que generamos ($$k$$) es mayor a la cantidad de registros que podemos mantener en memoria ($$C$$)? ¿Cómo podemos hacer el merge de las $$k$$ particiones?
Esto podría resolverse haciendo más de una pasada del merge: En vez de mergear las $$k$$ particiones, juntamos $$\sqrt{k}$$. Juntamos las primeras $$\sqrt{k}$$ particiones, luego las segundas $$\sqrt{k}$$, etc... Finalmente tendremos $$\sqrt{k}$$ particiones resultantes, ordenadas, y las podemos unir.
* Pero... ¿Y si la cantidad de particiones es tal que incluso haciendo lo anterior, no entran en memoria $$\sqrt{k}$$ registros (porque serían mayor a $$C$$)?
Vayamos a los números: En general se suele trabajar con computadoras de 8 o 16GB de memoria RAM. Supongamos que por diversas cuestiones, contamos con 512MB de memoria RAM a disposición de nuestro programa. No suena, hoy en día, un número tan grande (aunque puede serlo si el sistema debe realizar muchas tareas). Con lo que vimos anteriormente, podemos generar particiones de hasta tamaño (promedio) $$3C$$. Eso quiere decir que tendremos $$\frac{n}{3C}$$ particiones. Que no entren $$k$$ registros en memoria implicaría que $$\frac{n}{3C}$$ registros deberían ser mayor a $$C$$. Esto quiere decir que:

$$
\frac{n}{3C} > C
$$

$$
n > 3C^2
$$
	
Si nuestra memoria para el programa es de 512MB, donde supongamos que cada registro nos ocupe en promedio 128 Bytes (no solemos querer ordenar simples números). Eso querría decir que tenemos alrededor de $$C = 4.194.304$$ registros. Eso implicaría que nuestro $$n$$ debería ser mayor a $$5.28 \times 10^{13}$$ que, mantiendo que cada registro ocupe 128 bytes, implicaría que nuestro archivo original es de 6 Peta Bytes (ni siquiera Tera). Esas capacidades ni siquiera existen para fines remotamente cercanos a los de nuestra materia. Cuando llegamos a tales números, nos olvidaremos completamente de intentar implementar algoritmos de este estilo. Porque, a fin de cuentas... ¿Quién va a validar que esa gigantezca masa de datos está ordenada? El manejo de inmensos (o cuasi infinitos) volúmenes de datos es analizado en la materia _Organización de Datos_.
