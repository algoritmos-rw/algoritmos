---
title: Simulación de Administración de memoria
permalink: /tps/adminmemoria/
trabajo: Administracion de Memoria
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Administración de Memoria
=========================

En esta entrega haremos una breve simulación de lo que implica administrar memoria dinámica. Para esto, 
utilizaremos una librería implementada por el curso que simula el pedido explícito de memoria al Sistema
Operativo. Esto sólo lo realizaremos para esta breve entrega, a modo de ver lo que debe hacerse en otros
lenguajes de programación, así como lo que realizan los lenguajes con recolección de basura para hacer
estos pedidos sin que nos demos cuenta (tal como lo hace Go al hacer `new` o `make`).
**No** es necesario estudiar ni comprender el archivo del administrador.

El adjunto en [el sitio de descargas]({{site.skel}}) contiene el archivo con dicha librería, una definición
de los tipos `Vector` y `Persona`, y sus correspondientes pruebas. 

## Vector dinámico

Deberán leer el archivo `vector.go` con la documentación, e implementar las cuatro primitivas que faltan:
- `Destruir()`
- `Obtener()`
- `Guardar()`
- `Largo()`

En entregas futuras tendrán que implementar ustedes las Primitivas de creación y redimensión. Es importante notar
que **no** se volverá a utilizar el administrador de memoria, que sólo está planteado para esta entrega para
evaluar brevemente lo explicado de memoria dinámica. En futuras entregas deberán hacer uso directamente de las
funciones `new` (para los tipos de datos) y `make` (para arreglos/slices).


## Persona

Similar a la otra estructura, esta es simplemente una estructura anidada que representa en sí un árbol genealógico. 
La única primitiva necesaria para construir es la de `Destruir`, en la cual, si se invoca a "la cabeza de la familia", 
debe liberarse toda la memoria asociada a este, como también a sus descendientes. 


## Requisitos

Las implementaciones deben respetar los lineamientos de la documentación y, tal como lo hicieron con el TP0, deben lograr pasar todas las pruebas con OK.

La entrega se realizará de forma digital, subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

Importante: No enviar la entrega hasta tanto asegurarse que el programa compila, todas las pruebas dan OK y valgrind no reporta errores.


**No olviden revisar las [preguntas frecuentes de los TDA](/algo2/faq/tda)**
