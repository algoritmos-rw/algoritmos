---
title: TP0
permalink: /tps/tp0/
trabajo: TP0
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Trabajo Práctico 0
==================

El adjunto en [el sitio de descargas]({{site.skel}}) contiene varios archivos.
Deben editar el archivo `tp0.go`, completando las seis funciones que
aparecen en el código fuente: `Swap()`,  `Maximo()`, `Comparar()`, `Seleccion()`, `Suma()` y `EsCadenaCapicua()`.
Se puede ver en el archivo `tp0.go` la documentación que indica lo que debe hacer cada función. 

De todos los archivos que pueden encontrar en el sitio de descargas, sólo deben modificar `tp0.go`. 
El resto de archivos del zip no los deben modificar. Sí pueden, no obstante, leer el archivo `tp0_test.go` para entender qué verificaciones realizaremos sobre su código. 

Primero deben crear el módulo del tp0 en el directorio que vayan a usar para este (`go init tp0`). Para esta primera parte del tp deben crear un paquete llamado `ejercicios` que contenga tanto a `tp0.go` como a `tp0_test.go`. Luego, fuera de este paquete (en el nivel principal del módulo a implementar) debe haber un archivo que puede llamarse como gusten (por ejemplo `main.go`) que tenga el paquete main (obligatorio en todos los programas escritos en Go), donde estará el código del programa a implementar. 

En resumen, para funcionar correctamente deben tener una estructura de directorios y archivos como la siguiente:

```
tp0 (o como gusten llamarle al directorio del tp)
| -> main.go
| -> go.mod
| -> ejercicios
     | -> tp0.go
     | -> tp0_test.go
```

Recuerden hacer `go mod tidy`. Para la primera parte del tp simplemente pueden ejecutar

Las pruebas deben dar todas OK, y las pueden ejecutar con:

    cd ejercicios
    go test tp0_test.go

O simplemente:

	cd ejercicios
	go test
	

Luego que todas las pruebas ejecuten correctamente, deben implementar un programa (en el archivo principal, `main.go` que mencionamos antes) que: 
* Abra y lea de dos archivos de texto regulares (llamados `archivo1.in` y `archivo2.in`). Cada archivo tendrá varias líneas, donde en cada línea habrá un único número y nada más. En total, este archivo será la representación de un arreglo de números. Por ejemplo, el contenido de `archivo1.in` podría ser:
	```
	1
	7
	12
	8
	2
	1
	```
* Se debe leer cada uno de los archivos, y cargar en memoria los arreglos correspondientes, leyendo cada componente y convertir cada uno de los elementos a `int` (para lo que pueden utilizar la función `Atoi` del módulo `strconv`). Pueden asumir que no van a haber errores en las lecturas, ni letras donde deben haber números, etc...
* Una vez obtenidos los arreglos, se debe imprimir el arreglo que sea **mayor** entre los dos, de forma **ordenada**. Para esto, utilizar las funciones `Comparar` y `Seleccion` previamente implementadas. Para imprimir, hacerlo en el mismo formato que en el que vienen en los archivos. Es decir, una componente por línea. Si el arreglo más grande fuera `[2, 1, 7, 3]`, habría que imprimir:
	```
	1
	2
	3
	7
	```

La compilación (estando ubicados en el directorio principal del módulo) se realiza con el siguiente comando:

    go build tp0

Luego, pueden ejecutar el programa haciendo: 

	./tp0

Antes de realizar la entrega, es importante que cualquier archivo entregado cumpla con el formato de Go (en este caso particular, `tp0.go` y `main.go`, pero aplicar para cualquier entrega de aquí en más). Para lograr esto, simplemente deben correr el comando: 

	go fmt <nombre del archivo>

En este caso, `<nombre del archivo>` vendría a ser `tp0.go` (o `ejercicios/tp0.go`, si están parados desde el directorio del tp0, y no desde el de ejercicios).

La entrega se hará de forma digital subiendo el código a la [página de entregas de la materia]({{site.entregas}}).
Deben entregar un archivo `zip` con los entregables. Deben entregar un zip con todo el contenido del módulo. 

En caso de encontrarse con dificultades para armar el módulo como es descripto aquí, [les dejamos un video explicativo paso a paso para esta entrega](https://www.youtube.com/watch?v=IZrQt-vR3E4).

**No olviden revisar los [primeros pasos en Linux](/algoritmos/faq/primeros-pasos) y las [preguntas frecuentes](/algoritmos/faq/).**
