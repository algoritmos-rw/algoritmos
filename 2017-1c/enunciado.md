Twitter y una implementación del TT
===================================

Introducción
------------

Todos conocen la red social Twitter, donde cada persona puede seguir a otras, compartir contenido (imagenes, video, texto de hasta 140 caracteres). Ahora bien, también existe el Trending Topic (TT). Esto es, las tendencias de ciertos temas. Esto es teniendo en cuenta un determinado tiempo, frecuencia y lugar geográfico, pero nosotros nos vamos a centrar a nivel global. Cómo hace Twitter para llevar la cuenta de la cantidad de veces que se menciona cada hashtag? 
Una primera opción es, ya que se trata de cadenas, utilizar un diccionario. Dado que no nos interesa a priori tener un orden, y Twitter tiene que funcionar muy rápido, podríamos utilizar un TDA Hash. Ahora bien, supongan la cantidad de datos que procesa Twitter no es precisamente pequeña. Si almacenáramos todos los hashtags posibles (con un contador asociado), eventualmente nos quedaremos sin memoria. Esto no escala. Otra opción es que tengamos varios hashes en computadoras distintas (con comunicaciones en el medio), pero.. cómo sabemos en cuál computadora se encuentra la cantidad de menciones de #Algoritmos2?

Otra opción para mantener el uso de memoria constante es resignar un poco de precisión y utilizar algún algoritmo que realice una aproximación. Nosotros utilizaremos uno que se llama Counting Bloom Filters.

Counting Bloom Filters
----------------------

Supongamos que utilizaramos un arreglo de contadores. Cuando viene un nuevo hashtag, simplemente aumentamos en uno la posición que le corresponde dada una función de hashing. Si quisiéramos saber cuántas veces apareció una cadena, simplemente aplicamos la función de hashing, y vemos el contador en dicha posición. Y qué hacemos con las colisiones?

Es cierto que aquí si 3 palabras caen en la misma posición, se le van a sumar las apariciones, lo cual puede ser un problema. Ahora bien, supongamos que tenemos *2 contadores*, cada uno con una función de hashing diferente (y que creamos que es poco probable que esas mismas palabras vuelvan a colisionar). Entonces, podríamos decir que la cantidad de apariciones de una palabra es igual al mínimo de los contadores que le corresponden. Esto puede ser falso, porque se siguen contando otras colisiones, pero si tenemos K contadores, y tomamos el mínimo entre ellos, entonces podemos decir que si bien puede haber aparecido menos veces, seguro no más. Sigue siendo una aproximación, pero es mejor. 

Ventajas: 
	- El espacio ocupado es constante. Suponiendo que la cantidad de contadores (y funciones de hashing) es constante, y cada uno tiene un largo constante (considerable, pero constante), entonces nunca variará y nunca nos quedaremos sin memoria. 
	- Es aun más veloz que el hash, puesto que no hay redimensión posible. 

Desventajas:
	- A medida que aumenten la cantidad de elementos en los contadores, y vayan habiendo cada vez más colisiones, se volverá cada vez menos preciso. 
	- Acá no pueden haber bajas, o se nos van a empezar a complicar las cosas (si bien la estructura lo permite). Para el dominio de nuestro problema, esto no nos importa. 

Conclusión: Somos más veloces y ocupamos menos memoria, a cambio de ser menos precisos. Ahora bien, es poco probable que importe mucho si el TT n$^\circ$ 1 queda segundo en algún momento. 


Consigna
--------
Implementar un programa en C que lea por entrada estándar los usuarios y los hashtags de un mensaje. Dicho programa debe realizar las siguientes operaciones dependiendo de los parámetros que reciba:
	--TT: Para este comando, puede que la entrada estandar no termine nunca. Si recibe este parámetro, debe recibir otros dos, numéricos, a llamar N y K. El programa, cada N lineas (equivalentes a tweets) debe escribir por salida estandar los K Trending Topics. Pueden suponer que N y K serán valores tales que se pueden almacenar en memoria esa cantidad de cadenas (o estructuras auxiliares). aproximados, utilizando Counting Bloom Filters. Esto se debe a que no podemos asumir que la entrada estándar vaya a terminar jamás, por lo que almacenar todos los usuarios, tags, etc.. en memoria recordando la cantidad de apariciones es inviable.
	El tiempo de procesamiento de cada tag debe ser O(1), mientras que la impresión de los K TT debe realizarse en O(N log K).

	-o: Para este comando, se puede asumir que la entrada estándar es acotada. El programa, luego de terminar de leer dicha entrada, debe escribir por salida estándar, por cada cantidad de tags posibles, los usuarios que tienen dicha cantidad de tags (como lista). Cada lista debe encontrarse ordenada (alfanuméricamente). El procesamiento de cada línea debe realizarse en tiempo constante, mientras que la parte de impresión debe realizarse en tiempo O(U + T), siendo U la cantidad de usuarios que hayan, y T la cantidad de tags distintos que hubieran.
	Ejemplo:
		El Fede tiene 5 tags, Martín 3, Jorge 3, Javier 5, Nacho 8, Constanza 2, Agustina 5, Gonzalo 3, Matías 2, Joaquín 6, Ana 1, Juan 1
		Se debe escribir por salida estándar:
			1: Ana, Juan
			2: Constanza, Matias
			3: Gonzalo, Jorge, Martín
			5: Agustina, Fede, Javier
			6: Joaquín
			8: Nacho


El archivo, por cada línea tiene el formato siguiente:
```
Usuario1,tag1,tag2,...
Usuario2,tag3,tag4,...
Usuario1,tag5,tag1,...
```
Donde cada linea corresponde a un tweet realizado por el usuario mencionado, continuado por una los tags en dicho tweet. Por eso, un mismo usuario puede aparecer más de una vez. 

Para esto, contarán con un archivo de prueba provisto por el curso (poner link). Dicho archivo fue procesado de sus originales aquí (poner link). Consideren que puede haber un programa que capture tweets de la nube, los procese y escriba por salida estándar dicho tweet con este formato. 
Pueden crear otros archivos de pruebas que a ustedes les sirva para probar el programa. 
*Atención*: Tener en cuenta que el archivo provisto por el curso, descomprimido, ocupa medio GB, y cuenta con más 19 millones de líneas. Si quieren abrirlo para leerlo, recomendamos no utilizar un editor de texto que lo cargue en memoria, sino utilizar el comando de Linux `less`: `less tweets.txt`




