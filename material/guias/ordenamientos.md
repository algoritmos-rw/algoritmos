---
math: true
---

# Ordenamientos comparativos y no comparativos
{:.no_toc}

## Contenidos

1. TOC
{:toc}

## Ejercicio resuelto

Se tiene un arreglo de cadenas que representan fechas de la forma `YYYYMMDD` (ej: `20110626` representa el 26/06/2011). Implementar un algoritmo lineal que las ordene de forma creciente.

### Solución

Dado que todos los elementos van a ser fechas en un formato fijo, de mismo largo para cada uno, y bien definido qué es cada dígito, podemos aplicar Radix Sort. Ahora bien, tenemos dos formas:

1. Vamos de cifra menos significativa a más significativa, así como está definido, aplicando el ordenamiento interno. Esto sería, aplicar en cada una de las posiciones según el orden: 7, 6, 5, 4, 3, 2, 1, 0. No hay muchas más vueltas.
2. Considerar que no es necesario trabajar en base 10. Sabemos que si o si los días están en el rango 1-31. Los meses en el rango 1-12. Luego, en los años podríamos no tener esto acotado, y no conviene trabajar con un rango 1-9999 porque puede ser más grande que la cantidad de elementos a ordenar. Pero cuanto menos, nos ahorramos dos pasadas.

Algunas preguntas:

 - ¿Cuál es la mejor opción? La segunda, claramente. No sólo por hacerlo más rápido, sino por mostrar un entendimiento tanto del problema como del algoritmo.

 - ¿La otra opción está mal? No. Pero considerar que si nos piden un seguimiento, si no consideramos estas cosas vamos a demorar más. Y es tiempo que se nos consume del parcialito. Conviene más pensar primero, y luego ponerse a aplicar, que aplicar de entrada. Se termina ganando más tiempo. Ahora bien, si además es una cuestión de implementación, podría restar un poco no haberlo pensado de la mejor forma (esta es una aclaración general que puede depender de lo evidente que sea la mejora según el caso particular).

 _Aclaración_: en general este tipo de ejercicios pueden directamente implementarse en pseudo código, pero aquí proponemos una solución en Go para que puedan ver una resolución completa en dicho lenguaje.

 Aplicamos la primer solución, que es más corta:

```golang
func OrdenarFechas(fechas []string) {
    for i := 0; i < 8; i++ {
        ordenarPorDigito(fechas, 7 - i)
    }
}

func ordenarPorDigito(fechas []string, digito int) {
    digitos := make([]Lista[string], 10)
    for i := 0; i < 10; i++ {
        digitos[i] = CrearListaEnlazada[string]()
    }

    for fecha := range fechas {
        digitos[int(fecha[digito])].InsertarUltimo(fecha)
    }

    indice := 0
    for lista := range digitos {
        for iter := lista.Iterador(); iter.HaySiguiente(); iter.Siguiente(), indice++ {
            fechas[indice] = iter.VerActual()
        }
    }
}
```


Aplicamos la segunda solución, que es más rápida, pero hay que rebuscarse un poco más para no repetir 3 veces lo mismo:

```golang
func OrdenarFechas(fechas []string) {
    ordenarPorTiempo(fechas, 31, 6, 8);
    ordenarPorTiempo(fechas, 12, 4, 6);
    ordenarPorTiempo(fechas, 10000, 0, 4);
}

func ordenarPorTiempo(fechas []string, largo int, indiceIni int, indiceFin int) {
    tiempos := make([]Lista[string], largo)
    for i := 0; i < largo; i++ {
        tiempos[i] = CrearListaEnlazada[string]()
    }
    for fecha := range fechas {
        tiempo = int(fecha[indiceIni:indiceFin])
        tiempos[tiempo].InsertarUltimo(fecha)
    }
    indice := 0
    for lista := range dias {
        for iter := lista.Iterador(); iter.HaySiguiente(); iter.Siguiente(), indice++ {
            fechas[indice] = iter.VerActual()
        }
    }
}
```

## Ejercicios propuestos

1.	(★) Realizar un seguimiento de ordenar el siguiente arreglo utilizando Inserción, Selección, MergeSort,
    QuickSort y HeapSort. Contar la cantidad de operaciones (aproximadamente) para validar empíricamente
    la diferencia en el orden de cada uno, y poder comparar aquellos que sean iguales: `[1, 7, 5, 8, 2, 4, 9, 6, 5]`.

1.  (★) Implementar un algoritmo que permita ordenar de menor a mayor en $$\mathcal{O}(n)$$ un arreglo _casi_ ordenado
    de mayor a menor.

1.  (★) Se tiene un arreglo de números, como el del primer ejercicio (no necesariamente ese). Indicar cuál sería un
    algoritmo eficiente para ordenar dicho arreglo. [Aquí](soluciones/ordenamiento_nums.txt) la solución del ejercicio.

1.  (★★) Se tiene un arreglo de estructuras de la forma `type Evento struct {anio long, evento string}`, que indica el año y evento
    de un hecho definido a lo largo de la historia de la Tierra. Indicar y justificar cuál sería un
    algoritmo de ordenamiento apropiado para utilizar para ordenar dicho arreglo por año. Indicar también, si en vez
    de ordenar por año se decide ordenar por evento (lexicográficamente). Si se quiere ordenar por año y dentro de cada
    año, por evento: ¿Deben utilizarse para ambos campos el mismo algoritmo de ordenamiento? ¿Que característica/s deben
    cumplir dicho o dichos algoritmos para que quede ordenado como se desea? ¿En qué orden deben aplicarse los
    ordenamientos?

1.  (★★) Hacer el seguimiento de counting sort para ordenar por año las
    siguientes obras:

            1988 - Crónicas del Ángel Gris
            2000 - Los Días del Venado
            1995 - Alta Fidelidad
            1987 - Tokio Blues
            2005 - En Picada
            1995 - Crónica del Pájaro que Da Cuerda al Mundo
            1995 - Ensayo Sobre la Ceguera
            2005 - Los Hombres que No Amaban a las Mujeres

    ¿Cuál es el orden del algoritmo? ¿Qué sucede con el orden de los
    elementos de un mismo año, respecto al orden inicial, luego de
    finalizado el algoritmo? Justificar brevemente.

1.  (★★) Realizar el seguimiento de ordenar por Radix Sort el siguiente arreglo de cadenas que representan
    versiones. Cada versión tiene el formato `a.b.c`, donde cada valor `a`, `b` y `c` puede tener un
    valor entre 0 y 99. Considerar que se quiere que quede ordenado primero por la primera componente
    (`a`), luego por la segunda (`b`) y finalmente por la tercera (`c`). Se puede asumir que `a` nunca
    será 0 salvo que el número sea efectivamente 0. Es decir, la notación es _correcta_. Tener en cuenta que, por ejemplo
    `1.1.3 < 1.1.20`,  `2.20.8` < `3.0.0`.

    ```
    ["4.3.2", "5.1.2", "10.1.4", "2.1.20", "2.2.1", "4.2.3",
    "2.1.5", "8.1.2", "5.30.1", "10.0.23"]
    ```

1.  (★★) Indicar Verdadero o Falso, justificando de forma concisa en cualquier caso.

    a. Podríamos mejorar el orden de complejidad de QuickSort si contaramos con más información sobre
    cómo son los datos a ordenar.

    b. No siempre conviene utilizar Counting Sort para ordenar un arreglo de números enteros.

    c. Que un algoritmo de ordenamientos sea estable implica que el algoritmo ordena sobre el arreglo original
    (sin utilizar otro adicional). Por ejemplo, Counting Sort no es estable.

1.  (★★★★) Se quiere ordenar un arreglo de películas por su género. No se conoce cuántos, ni cuáles son estos géneros,
    pero se sabe que son muy pocos comparando con la cantidad de películas a ordenar. Diseñar un algoritmo que
    permita ordenar las películas en tiempo lineal de la cantidad de películas y explique ćomo funcionaría sobre las
    siguientes películas:

    - Donnie Darko (2001): Thriller psicológico
    - Juno (2007): Coming of age
    - The Shining (1980): Thriller psicológico
    - Labyrinth (1986): Fantasía
    - Ferris Bueller's Day Off (1986): Coming of age

1.  (★★★) $$\spadesuit$$ Se tiene una larga lista de números de tres cifras `abc` que representan números
    en notación científica de la forma: $$a,b \cdot 10^c$$. Por ejemplo 123 representaría el número
    $$1,2 \cdot 10^3$$.

    {:.lower_alpha}
    1.  Diseñe un algoritmo para ordenar los números según su valor en notación científica. ¿De qué orden es?

     1.  Muestre cómo se ordena la siguiente lista de números con el algoritmo que diseñó:

         $$[ 122, 369, 332, 180, 486, 349, 326, 101 ]$$

         que representan

         $$[1,2 \cdot 10^2; 3,6 \cdot 10^9; 3,3 \cdot 10^2; 1,8 \cdot 10^0; 4,8 \cdot 10^6; 3,4 \cdot 10^9; 3,2 \cdot 10^6; 1,0 \cdot 10^1]$$,

         y equivalen a $$[120; 3600000000; 330; 1,8; 4800000; 3400000000; 3200000; 10 ]$$.

1.	(★★★★) Suponer que se tiene un arreglo de $$n$$ elementos ordenados, seguido de $$f(n)$$
    elementos desordenados. Cómo ordenarías el arreglo según si $$f(n)$$ es:

    a. $$f(n) = \mathcal{O}(1)$$

    b. $$f(n) = \mathcal{O}(\log{n})$$

    c. $$f(n) = \mathcal{O}\left(\sqrt{n}\right)$$

1.  (★★★★★) Implementar un algoritmo que, dado un arreglo de $$n$$ números enteros cuyos valores van
    de $$0$$ a $$K$$ (constante conocida), procese dichos números en tiempo $$\mathcal{O}(n + K)$$, devuelva alguna
    estructura que permita consultar cuántos valores ingresados están en el intervalo `(A, B)`, en tiempo
    $$\mathcal{O}(1)$$. Explicar cómo se usaría dicha estructura para poder realizar tales consultas.
    
1.  (★★) ¿Puede aplicarse counting sort a un arreglo de _floats_ cuyos valores se encuentran entre 0 y 1? 
    En caso de poderse, explicar cómo lo harías. En caso de no poderse, explicar por qué y mencionar 
    un algoritmo que resuelva el problema, en un orden semejante al de counting sort. ¿Necesitarías
    más información para aplicar dicho algoritmo, o con saber que el rango es de 0 a 1 es suficiente?
    
1.  (★★★★★) Se tiene un conjunto de $$n$$ tuercas y otro conjunto de $$n$$ tornillos. No podemos comparar a los 
    tornillos entre sí, ni a las tuercas entre sí, pero podemos comparar un tornillo con una tuerca 
    (ver si un tornillo y una tuerca hacen pareja, si el tornillo es más grande o más chico de lo debido). 
    Implementar un algoritmo que en $$\mathcal{O}(n \log n)$$ determine todas las parejas de 
    tuercas-tornillos. 

1. (★★★) $$\spadesuit$$ Implementar en Go un algoritmo de RadixSort para ordenar un arreglo de Alumnos 
   (estructuras) en función de sus notas en parcialitos, de menor a mayor. Los alumnos 
   tienen su nombre y las notas (numéricas, 0-10) de los 3 parcialitos (tenemos las 
   notas finales). El arreglo debe quedar ordenado primero por el promedio de notas. 
   No importan los decimales, nada más si tuvo "promedio 9", "promedio 8", etc., es 
   decir la parte entera del promedio. Luego, en caso de igualdad en este criterio, los 
   alumnos deben quedar ordenados por la nota del parcialito 1, en caso de persistir 
   la igualdad, la del parcialito 2, y finalmente por la del 3. En ningún caso se 
   utiliza el nombre para desempatar. 
   Suponer que cualquier algoritmo de ordenamiento auxiliar que se requiera ya se encuentra
   implementado. Sí justificar por qué se utiliza el o los algoritmos auxiliares utilizados, 
   y no otros. Indicar y justificar la complejidad del algoritmo. El desarrollo de la
   complejidad debe estar completo, no se aceptan resultados parciales. 
   Hacer un seguimiento sobre el siguiente ejemplo. No es necesario hacer el seguimiento 
   de cómo funciona el o los algoritmos auxiliares.

   ```
   Juan Pérez, 7, 4, 5              Hector Fernández, 8, 9, 10
   María Gómez, 5, 7, 4             Martina Giménez, 7, 4, 4
   Germán González, 4, 8, 5         Mirtha Legrand, 10, 8, 10
   Elián Valenzuela, 4, 2, 0        Ricardo Bonafide, 4, 6, 8
   Bobo Weghorst, 0, 0, 0
   ```
  
1. (★★★) $$\spadesuit$$ Implementar un algoritmo de ordenamiento, que sea lineal, 
   que permita definir el orden en una fila de personas para comprar una 
   Cajita CampeónFeliz en un establecimiento de comida rápida. Los datos 
	  (`structs`) a ordenar cuentan con edad (número), nombre (string) y nacionalidad 
	  (enumerativo, de 32 valores posibles). Primero deben ir los niños 
	  (todos con edad menor o igual a 12), y estos deben ordenarse por edad 
	  (de menor a mayor), independientemente de la nacionalidad. Luego deben ir los 
	  "no niños", que primero deben estar ordenados por nacionalidad (segundo 
	  Francia, por ejemplo) y en caso de igualdad de nacionalidad, por edad, 
	  también de menor a mayor.
	  En caso de necesitar algún ordenamiento auxiliar (en caso que una parte del
	  algoritmo implique hacer BucketSort o RadixSort), puede considerarse como 
	  ya implementado, pero justificar (en caso de necesitar justificación) 
	  por qué puede utilizarse dicho algoritmo dadas las condiciones del problema.
	  Justificar la complejidad de la función implementada. El desarrollo de la
	  complejidad debe estar completo para el problema en cuestión, no se aceptarán
	  resultados parciales genéricos.

1.  (★★★★) Se tiene un arreglo de $n$ cadenas y una **buena función de hashing**. Se quiere
    ordenar dichas cadenas por su resultado en la función de hashing, habiéndole
    hecho previamente `% K` a cada uno de los resultados (donde $K$ es un valor
    enorme, muchísimo más grande que $n$). Implementar un algoritmo que ordene las 
    cadenas por dicho criterio en $\mathcal{O}(n)$. La firma de la función debe ser:
    `func Ordenar(cadenas []string, valoresHash []int64, K int64) []string`. 
    `valoresHash` ya tiene cada valor posterior a haber hecho `% K`.
    Recomendamos recordar las propiedades de las funciones de hashing.
    Si necesitás un algoritmo de ordenamiento auxiliar al que estés implementando,
    podés considerarlo ya implementado. 
    Justificar brevemente por qué es correcta la aplicación del algoritmo que implementaste.
    Justificar la complejidad del algoritmo implementado. 

    Por ejemplo, si queremos ordenar las cadenas: `gato, perro, elefante, comadreja`
    y los resultados de aplicarles la función de hashing (y `% K`) son `19, 703, 9872, 37`, respectivamente, 
    las cadenas deben de quedar: `gato, comadreja, perro, elefante`.

    En caso que estés viendo este ejercicio antes de haber visto Hashes (es decir, inmediatamente después de
    la clase de ordenamientos), esperá a ver ese tema, que es la clase inmediatamente siguiente. 

1.  (★★) Realizar el seguimiento de aplicar RadixSort al siguiente conjunto de partidos
    de fútbol. El resultado debe quedar ordenado primero por cantidad de goles del
    partido, y en caso de igualdad, por diferencia de gol entre rivales. No es necesario
    hacer el seguimiento del algoritmo auxiliar, pero si indicar cuál sería y por qué. 

    ```
    Argentina 6 - Serbia y Montenegro 0; Brasil 1 - Alemania 7; España 1 - Paises Bajos 0;
    Francia 4 - Croacia 2; Argentina 3 - Croacia 0; Brasil 2 - Alemania 0;
    Polonia 0 - México 0; Argentina 2 - Australia 1; Brasil 1 - Chile 1;
    Argentina 2 - Inglaterra 0; Alemania 3 - Italia 3; Liechtenstein 0 - San Marino 1
    ```
