# FAQ - Enlaces simbólicos en Unix
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo reutilizar el código que hacemos sin copiar y pegar?

La idea de los TDAs que implementamos es también poder reutilizarlos en el futuro. 
Por esto es que se diseñan para trabajar con datos genéricos. Un ejemplo de esto
pueden ser los TPs donde reutilizamos los TDAs anteriormente implementados, 
así como el Hash Abierto reutiliza la Lista, o el ABB reutiliza la Pila. 

El problema al que nos encontramos parte escencialmente de una limitación de cómo
realizan las entregas: al realizar una entrega, envían código de un TDA en particular
con su módulo, pero también debemos enviar las dependencias, y estas debe ser incluídas
como un submódulo. Esto nos implica de alguna forma copiarnos el código de dicha entrega
para pegarlo en una subcarpeta, lo cual es indeseable. Desde el vamos, es poco práctico,
y si llegamos a encontrar algún problema debemos asegurarnos de actualizar todas las
copias. Si el código duplicado es un problema, esto lo puede ser mucho más. 

En general, en el alcance de la materia, difícilmente deberían necesitar modificar código 
anterior, pero no por esto vamos a decidir no mencionar en un problema de desarrollo que
puede acarrear grandes problemas. 

La forma sencilla de resolver esto (sin complejizar la estructura de módulos y directorios)
será utilizando enlaces simbólicos.

### ¿Qué es un enlace simbólico?

Un enlace simbólico es un archivo que hace referencia a otro. Sería el equivalente a un
puntero a nivel de archivos. A nivel usuario, es semejante a un acceso directo. Pero es
importante notar que no es simplemente un acceso directo, y que a cualquier operación
sobre dicho archivo es completamente equivalente a realizarlo sobre el original. 
Por ejemplo, podríamos tener en nuestro IDE un directorio donde se encuentre un enlace
simbólico a otro archivo, y podríamos leerlo (y modificarlo) directamente como si lo
hiciérmos sobre el original. 

Para crear un enlace simbólico, simplemente debemos hacer: 

```
	~ $ ln -s PATH-A-ARCHIVO-ORIGINAL <NOMBRE-ENLACE-SIMBOLIC>
```
(En caso de no indicar el nombre del enlace simbólico, será el del archivo original)

### ¿Cómo utilizaríamos los enlaces simbólicos?

Supongamos que yo tengo una estructura de directorios de la siguiente forma: 
```
AlgoritmosII
	|
	-> TP0
	-> Pila
	-> Cola
	-> Lista
	-> Hash
	-> ...
```

Supongamos que para implementar el Hash voy a utilizar la lista (HashAbierto). 
Entonces lo que podemos hacer es lo siguiente: 

```
AlgoritmosII $ cd Hash
Hash $ ln -s ../lista lista
```

Automáticamente ahora tendremos dentro de nuestro directorio un link simbólico al directorio
de lista, y podemos acceder a este desde `hash/lista`. Esto permite no tener que copiar código,
pero además permite lo siguiente: si armamos el zip (con el comando zip), automáticamente
los enlaces simbólicos se _expandirán_ ya agregándonos los archivos que necesitamos para nuestra
entrega. 

¿Esto resolvería el problema en cualquier caso? Es más que probable que no, pero al alcance de nuestra
materia seguramente lo cubre, y no valga la pena hacernos con una solución más sofisticada. 

