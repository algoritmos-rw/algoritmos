Twitter y una implementación del TT
===================================

Introducción
------------

Twitter es una red social basada en la publicación mensajes cortos, llamados tweets. Una de las características de esta red es la publicación de los temas más comentados del momento, llamados trending topics (TT). Los usuarios pueden contribuir a la popularidad de ciertos temas mencionándolos usando un caracter numeral, por ejemplo `#Algoritmos2`. A estas menciones se las llama hashtags. El objetivo de este trabajo práctico es modelar un sistema que calcule los TTs de una serie de tweets.
¿Cómo hace Twitter para llevar la cuenta de la cantidad de veces que se menciona cada hashtag? 

Counting Bloom Filters
----------------------

Almacenar lo que potencialmente pueden ser millones de hashtags puede ser requerir mucha infraestructura, y muchas veces alcanza con tener una aproximación. Utilizaremos este enfoque para realizar este trabajo práctico.
Para esto se propone usar una idea basada en el funcionamiento de las tablas de hash. Simplemente almacenaremos la cantidad de apariciones de cada hashtag en un arreglo, al que accederemos a través de una función de hashing. Por lo tanto, si `f("Algoritmos2") = 4`, incrementaremos en uno el valor almacenado en la posición 4 de nuestro arreglo. A esta técnica se la llama counting bloom filters.

Es cierto que aquí si 3 palabras caen en la misma posición, se le van a sumar las apariciones, lo cual puede ser un problema. Supongamos que tenemos *2 contadores*, cada uno con una función de hashing diferente (y que creamos que es poco probable que esas mismas palabras vuelvan a colisionar). Entonces, podríamos decir que la cantidad de apariciones de una palabra es igual al mínimo de los contadores que le corresponden a cada una. Esto puede ser falso, porque se siguen contando otras colisiones, pero si tenemos _K_ contadores, y tomamos el mínimo entre ellos, entonces podemos decir que si bien puede haber aparecido menos veces, seguro no más. Sigue siendo una aproximación, pero es mejor. 

Consigna
--------
Implementar dos programas en C:
	- procesar_tweets: 
	Este programa se utilizará para contar los trending topics en un conjunto de tweets, leyendo cada línea proveniente de la *entrada estándar*. Como se sabe que la cantidad de mensajes puede ser ilimitada, para usarlo se requieren dos parámetros enteros, llamados _n_ y _k_. El programa deberá imprimir por *salida estándar* el histórico de los _k_ TTs aproximados cada _n_ lineas, ordenados por ocurrencias. Pueden suponer que _n_ y _k_ serán valores tales que se pueda almacenar en memoria esa cantidad de cadenas o estructuras auxiliares.
	El tiempo de procesamiento de cada tag debe ser _O(1)_, mientras que la impresión de los _k_ TT debe realizarse en _O(n log k)_.
	
	Ejemplos de invocación:
		`~$ cat tweets.txt | ./procesar_tweets 300000 20` 
		
	- procesar_usuarios: Este programa tendrá como objetivo contar la cantidad de hashtags que usa cada usuario, leyendo cada línea del archivo pasado por parámetro. Como se sabe que la cantidad de usuarios es mucho menor a la cantidad de TTs, y que dicho archivo termina, consideramos que se puede almacenar en memoria todo lo necesario para procesar la entrada.
	El programa deberá procesar la entrada y luego deberá escribir por *salida estándar* los usuarios y la cantidad de hashtags que utilizaron en tiempo lineal: _O(u + t)_ siendo _u_ la cantidad de usuarios encontrados y _t_ la cantidad de hashtags diferentes, ordenados según ocurrencias, y dentro de cada ocurrencia, ordenado alfanuméricamente.
	
	Ejemplo de invocación:
		`~$ ./procesar_tweets tweets.txt` 
		
	Ejemplo de salida:
		El usuario Fede tiene 5 tags, Martín 3, Jorge 3, Javier 5, Nacho 8, Constanza 2, Agustina 5, Gonzalo 3, Matías 2, Joaquín 6, Ana 1, Juan 1
		Se debe escribir por salida estándar:
		```
			1: Ana, Juan
			2: Constanza, Matias
			3: Gonzalo, Jorge, Martín
			5: Agustina, Fede, Javier
			6: Joaquín
			8: Nacho
		```
		
La entrada estandar debe tener el siguiente formato:
```
Usuario1,tag1,tag2,...
Usuario2,tag3,tag4,...
Usuario1,tag5,tag1,...
```
Donde cada linea corresponde a un tweet realizado por el usuario mencionado, continuado por una los tags en dicho tweet. Por eso, un mismo usuario puede aparecer más de una vez. No hay líneas que no contengan al menos un tag. 

Para esto, contarán con un [archivo de prueba provisto por el curso](https://drive.google.com/file/d/0B_oxuLrlET2hU1ZYbDJ2LXY1Z2s/view?usp=sharing). Dicho archivo fue procesado de sus originales [aquí](https://snap.stanford.edu/data/twitter7.html). Consideren que puede haber un programa que capture tweets de la nube, los procese y escriba por salida estándar dicho tweet con este formato. 
Pueden crear otros archivos de pruebas que a ustedes les sirva para probar el programa. 
*Atención*: Tener en cuenta que el archivo provisto por el curso, descomprimido, ocupa medio GB, y cuenta con más 19 millones de líneas. Si quieren abrirlo para leerlo, recomendamos no utilizar un editor de texto que lo cargue en memoria, sino utilizar el comando de Linux `less`: `less tweets.txt`.

Criterios de aprobación
-----------------------
El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores de memoria. La entrega incluye, obligatoriamente, un pequeño informe en formato PDF para explicar la complejidad de cada uno de los algoritmos utilizados, y todos los archivos que correspondan a la elaboración del TP, modularizado como les parezca adecuado. Recomendamos crear un TDA CountingFilters, para lograr que el código quede modularizado de la mejor forma. Además, debe adjuntarse un archivo makefile para la compilación del programa. 
La fecha de entrega del TP es el (indicar fecha).

La entrega se realiza:
	1. por mail a la casilla de TPs (`tps.7541rw@gmail.com`): todos los archivos en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. En el asunto deben indicar: TP1 - <Padrón1> - <Apellido1> - <Padrón2> - <Apellido2>. *No adjuntar el archivo de pruebas provisto por el curso.*  
	2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código. No es necesario reimprimir el código de los TDA.
