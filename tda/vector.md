---
title: Vector dinámico
permalink: /tps/vector/
trabajo: Vector
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Vector dinámico
===============

El adjunto en [el sitio de descargas]({{site.skel}}) contiene una definición del tipo de dato _vector dinámico_ que deberán completar.

En particular, deberán leer el archivo `vector.h` con la documentación, e implementar en
`vector.c` las cuatro primitivas que faltan:

- `vector_destruir()`
- `vector_obtener()`
- `vector_guardar()`
- `vector_largo()`

Además, deberán estudiar la implementación propuesta de las siguientes dos primitivas:

- `vector_crear()`
- `vector_redimensionar()`

(En entregas futuras, se pedirá la implementación completa del tipo abstracto, incluyendo la creación y redimensionado.)

La implementación debe respetar los lineamientos de la documentación y tal como lo hicieron con el TP0 deben lograr pasar todas las pruebas con OK.

Deben entregar una hoja de papel, con su nombre y padrón,
**imprimiendo únicamente las funciones que implementaron ustedes**.

Además, deben subir el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

Importante: No enviar el mail hasta tanto asegurarse que el programa compila sin warnings, todas las pruebas dan OK y valgrind no reporta errores.

Usar la misma linea provista para el tp0 para compilar. Para correr Valgrind, usar:

    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

**No olviden revisar las [preguntas frecuentes de los TDA](/algo2/faq/tda)**
