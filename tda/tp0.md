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

Para esta parte del tp0, deben crear un paquete que contenga tanto a `tp0.go` como a `tp0_test.go`. Dicho paquete ha de llamarse `ejercicios`. Luego, fuera de este paquete (en el nivel principal del módulo a implementar) debe haber un archivo que puede llamarse como gusten (por ejemplo `main.go`) que tenga el paquete `main` sí o sí, donde estará el programa a implementar. 
Además deben de tener el archivo `go.mod` que es el árchivo del módulo del tp. Es decir, para funcionar correctamente deben tener una estructura de directorios como la siguiente: 

```
tp0 (o como gusten llamarle al directorio del tp)
| -> main.go
| -> go.mod
| -> ejercicios
     | -> tp0.go
     | -> tp0_test.go
```

La compilación (estando ubicados en el directorio donde se encuentren los archivos) se realiza con el siguiente comando:

    go build tp0

Las pruebas deben dar todas OK, y las pueden ejecutar con:

    cd ejercicios
    go test tp0_test.go

O simplemente:

	cd ejercicios
	go test
	

Luego que todas las pruebas ejecuten correctamente, deben implementar un programa (en el archivo principal, `main.go` que mencionamos antes) que: 
* Lea dos archivos fijos (se llaman si o si `archivo1.in` y `archivo2.in`). Cada archivo tendrá dentro escrito un arreglo en texto, donde cada componente está separado por comas. Es decir, un ejemplo podría ser que en `archivo1.in` hay escrito `1, 7, 12, 8, 2, 1`. Cada archivo tiene una única línea, que define un único arreglo. Deben leer cada uno de los archivos, y obtener los arreglos correspondientes, separando cada componente (para lo que pueden utilizar la función `split` del módulo `strings`) y convertir cada uno de los elementos a `int` (para lo que pueden utilizar la función `Atoi` del módulo `strconv`). Pueden asumir que no van a haber errores en las lecturas, ni letras donde deben haber números, etc... 
* Una vez obtenidos los arreglos, deben imprimir **ordenado** el arreglo que sea **mayor** entre los dos. Para esto, utilizar las funciones `Comparar` y `Seleccion` previamente implementadas. Para imprimir, hacerlo en el mismo formato que en el que vienen en los archivos. Es decir, cada componente separados por una coma. Si el arreglo más grande fuera `2, 1, 7, 3`, habría que imprimir `1, 2, 3, 7`. 

Antes de realizar la entrega, es importante que cualquier archivo entregado cumpla con el formato de Go (en este caso particular, `tp0.go`, pero aplicar para cualquier entrega de aquí en más). Para lograr esto, simplemente deben correr el comando: 

	go fmt <nombre del archivo>

En este caso, `<nombre del archivo>` vendría a ser `tp0.go` (o `ejercicios/tp0.go`, si están parados desde el directorio del tp0, y no desde el de ejercicios).

La entrega se hará de forma digital subiendo el código a la [página de entregas de la materia]({{site.entregas}}).
Deben entregar un archivo `zip` con los entregables. Deben entregar un zip con todo el contenido del directorio (en particular, el archivo principal y `tp0.go`). 

En caso de encontrarse con dificultades para armar el módulo como es descripto aquí, [les dejamos un video explicativo paso a paso para todas las entregas](https://www.youtube.com/watch?v=IZrQt-vR3E4).

**No olviden revisar los [primeros pasos en Linux](/aed/faq/primeros-pasos) y las [preguntas frecuentes](/aed/faq/).**
