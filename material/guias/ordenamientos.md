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

 _Aclaración_: en general este tipo de ejercicios pueden directamente implementarse en pseudo código, pero aquí proponemos una solución en C para que puedan ver una resolución completa en dicho lenguaje.

 Aplicamos la primer solución, que es más corta:

```cpp
void ordenar_fechas(char** fechas, size_t n) {
    for (size_t i = 0; i < 8; i++) {
        ordenar_por_digito(fechas, 7 - i, n);
    }
}

void ordenar_por_digito(char** fechas, size_t digito, size_t n) {
    lista_t* digito[10];
    for (size_t i = 0; i < 10; i++) digito[i] = lista_crear();

    for (size_t i = 0; i < n; i++) {
        int valor = char_a_int(fecha[i][digito]);
        lista_insertar_ultimo(digito[valor], fecha);
    }

    size_t indice = 0;
    for (size_t i = 0; i < 31; i++) {
        while(!lista_esta_vacia(digito[i])) {
            fechas[indice++] = lista_borrar_primero(digito[i]);
        }
        lista_destruir(digito[i], NULL);
    }
}

```


Aplicamos la segunda solución, que es un tanto más larga, pero más rápida:

```cpp
void ordenar_fechas(char** fechas, size_t n) {
    ordenar_por_dia(fechas, n);
    ordenar_por_mes(fechas, n);
    ordenar_por_anio(fechas, n);
}

int char_a_int(char v) {
    return a - '0';
}

void ordenar_por_dia(char** fechas, size_t n) {
    lista_t* dias[31];
    for (size_t i = 0; i < 31; i++) dias[i] = lista_crear();

    for (size_t i = 0; i < n; i++) {
        int dia = char_a_int(fecha[i][6]) * 10 + char_a_int(fecha[i][7]) - 1;
        lista_insertar_ultimo(dias[dia], fecha);
    }

    size_t indice = 0;
    for (size_t i = 0; i < 31; i++) {
        while(!lista_esta_vacia(dias[i])) {
            fechas[indice++] = lista_borrar_primero(dias[i]);
        }
        lista_destruir(dias[i], NULL);
    }
}

void ordenar_por_mes(char** fechas, size_t n) {
    lista_t* meses[12];
    for (size_t i = 0; i < 12; i++) meses[i] = lista_crear();

    for (size_t i = 0; i < n; i++) {
        int mes = char_a_int(fecha[i][4]) * 10 + char_a_int(fecha[i][5]) - 1;
        lista_insertar_ultimo(meses[mes], fecha);
    }

    size_t indice = 0;
    for (size_t i = 0; i < 31; i++) {
        while(!lista_esta_vacia(meses[i])) {
            fechas[indice++] = lista_borrar_primero(meses[i]);
        }
        lista_destruir(meses[i], NULL);
    }
}

void ordenar_por_anio(char** fechas, size_t n) {
    for (size_t i = 0; i < 4; i++) {
        ordenar_por_digito(fechas, 3 - i, n);
    }
}

```

Ahora vemos de mejorar un poco el código:

```cpp
void ordenar_fechas(char** fechas, size_t n) {
    ordenar_por_dia(fechas, n);
    ordenar_por_mes(fechas, n);
    ordenar_por_anio(fechas, n);
}

int char_a_int(char v) {
    return a - '0';
}

void ordenar_por_dos_digitos(char** fechas, size_t n, size_t digito_ini,
                             size_t max) {
    lista_t* dias[max];
    for (size_t i = 0; i < max; i++) dias[i] = lista_crear();

    for (size_t i = 0; i < n; i++) {
        int dia = char_a_int(fecha[i][digito_ini]) * 10
                + char_a_int(fecha[i][digito_ini + 1]) - 1;
        lista_insertar_ultimo(dias[dia], fecha);
    }

    size_t indice = 0;
    for (size_t i = 0; i < max; i++) {
        while(!lista_esta_vacia(dias[i])) {
            fechas[indice++] = lista_borrar_primero(dias[i]);
        }
        lista_destruir(dias[i], NULL);
    }
}


void ordenar_por_dia(char** fechas, size_t n) {
    ordenar_por_dos_digitos(fechas, n, 6, 31);
}

void ordenar_por_mes(char** fechas, size_t n) {
    ordenar_por_dos_digitos(fechas, n, 4, 12);
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

1.  (★★) Se tiene un arreglo de estructuras de la forma `struct {long anio, char* evento}`, que indica el año y evento
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
    (`a`), luego por la segunda (`b`) y finalmente por la tercera (`c`). Tener en cuenta que, por ejemplo
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

1.  (★★★) Se tiene una larga lista de números de tres cifras `abc` que representan números
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
