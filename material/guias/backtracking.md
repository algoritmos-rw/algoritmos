---
math: true
---

# Backtracking
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Se tiene una lista de materias que deben ser cursadas en el mismo cuatrimestre, cada materia está representada con una lista de cursos/horarios posibles a cursar (solo debe elegirse uno de todos ellos). Cada materia puede tener varios cursos.

Implementar el pseudocódigo de un algoritmo de backtracking que devuelva un listado con todas las combinaciones posibles que permitan asistir a un curso de cada materia sin que se solapen los horarios.
Considerar que existe una función `son_compatibles(curso_1, curso_2)` que dados dos cursos devuelve un valor booleano que indica si se pueden cursar al mismo tiempo.

### Solución

Lo primero que hay que tratar de entender, es que es necesario tratar de ir generando las combinaciones hasta encontrar alguna válida. Por fuerza bruta, sería obtener primero todas las combinaciones de materias (un curso por cada materia) y luego ver cuáles son incompatibles para filtrar.
Suponiendo que todas las materias tenga _k_ cursos, y que tenemos _n_ materias, tendríamos un orden de $$\mathcal{O}(k^n)$$ para generar cada combinacion (pues hay $$k^n$$ combinaciones, supondremos que generar cada una costará a lo sumo $$\mathcal{O}(n)$$, despreciable al lado del otro término aunque _k_ fuere constante o muy pequeño).
Luego, sería necesario filtrar las opciones incorrectas, pero esto lo vamos a obviar porque la idea es plantear que esto no sea necesario. La idea va a ser ir generando todas esas combinaciones posibles, pero en cuanto detectemos que una opcion no es válida, simplemente descartarla.

Por ejemplo, si ya sabemos que el primer curso de Algoritmos y Programación II no es compatible con el primer curso de Álgebra II, por qué ver todas las combinaciones que incluyan estos dos cursos? Ya podemos descartarlas al encontrar esta colisión. En el peor de los casos, todos los cursos son compatibles entre sí sin colisión y mantendremos el orden (aunque siendo realistas, esto no sucede ni cuando las materias son de curso único).

Por lo tanto, allí estará la poda: cuando detectemos que un curso es incompatible con el resto, descartamos la opción. Simplemente con analizar si la ultima materia agregada en cada paso es compatible con las anteriores, será suficiente (luego, no es necesario validar la primera con la segunda, la primera con la tercera, etc... porque eso ya debería haberse hecho). De esta forma reducimos el costo de esa poda de $$\mathcal{O}(n^2)$$ a $$\mathcal{O}(n)$$.

``` python
def horarios_posibles(materias, solucion_parcial):
    # Si no nos quedan materias por ver
    if len(materias) == 0:
        if solucion_posible(solucion_parcial):
            return [solucion_parcial]
        else:
            return []

    # No es solucion total, pero es solucion parcial?
    if not solucion_posible(solucion_parcial):
        return []

    # Caso general, por ahora la solucion parcial es aceptada:
    materia_actual = materias.ver_primero()
    materias.borrar_primero()

    soluciones = []

    for curso in materia_actual:
        # Si devuelve una lista con soluciones parciales, se agregaran todas a esta lista. Si devuelve lista vacia, no hara nada
        soluciones.extend(horarios_posibles(materias_restantes, solucion_parcial + [curso]))

    # Si interesa volver a poner la materia que sacamos:
    materias.guardar_primero(materia_actual)

    return soluciones

def solucion_posible(horarios):
    ultimo = horarios.ver_ultimo()
    for curso in horarios (salvo el ultimo):
        if not son_compatibles(curso, ultimo):
            return False
    return True
```

## Ejercicios propuestos

1. Diseñar un algoritmo de backtracking que resuelva el siguiente problema: dado una pieza de caballo de ajedrez (_knight_, o caballero) dentro de un tablero, determinar los movimientos a hacer para que el caballo logre pasar por todos los casilleros, una única vez.

   Recordar que el caballo se mueve en forma de L (dos casilleros en una dirección, y un casillero en dirección perpendicular).

2. Escribir en pseudocódigo un algoritmo de tipo Backtracking que reciba una cantidad de dados _n_ y una suma _s_. La función debe imprimir todas las tiradas posibles de n dados cuya suma es s. Por ejemplo, con `n = 2` y `s = 7`, debe imprimir `[1, 6] [2, 5] [3, 4] [4, 3] [5, 2] [6, 1]`.

   ¿De qué orden es el algoritmo en tiempo y memoria?

3. Escribir una función en pseudocódigo que, utilizando backtracking, dada una lista de enteros positivos _L_ y un entero _n_ devuelva todos los subconjuntos de _L_ que suman exactamente _n_. ¿Cómo cambia el comportamiento del algoritmo frente a una solución por fuerza bruta? Explicar con al menos dos ejemplos de _L_ y _n_.
[(Solución)](soluciones/subset_sum.py)

4. ¡Ejercicio difícil! Realizar el ejercicio anterior, si además se agregar como restricción que no se puede utilizar más de una vez un mismo elemento de la lista L, pero se quieren maximizar la cantidad de conjuntos obtenidos.

## Bibliografía y referencias

- Weiss, Mark Allen: "Data Structures and Algorithms" (tercera edición), Pearson, 1999. Cap. 10.5: _Backtracking algorithms_.
- Kruse, Robert Leroy;  Tondon, Clovis L.;  Leung, Bruce P: "Data structures and program design in C", Prentice-Hall, 1997. Cap 5.3: _Backtracking: Postponing the Work_.
- Guerequeta, Rosa; Vallecillo, Antonio: "Técnicas de Diseño de Algoritmos" (segunda edición), Servicio de Publicaciones de la Universidad de Málaga, 1998. Cap 6: _Vuelta atrás_.
