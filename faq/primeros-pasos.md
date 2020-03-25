# FAQ - Primeros Pasos con Linux y C
{:.no_toc}

* Contenido
{:toc}

### Escribir un hello world en C

El primer paso es escribir el código del programa en el editor o IDE, y guardarlo en un archivo con extensión `.c`.

Lo mejor es que comiencen por un “Hola mundo”, escribiendo en el editor:

```cpp
#include <stdio.h>

int main(void) {
    printf("Hola mundo");
    return 0;
}
```

Lo guardan en un archivo llamado `hola.c`.

Es importante notar que todo programa de C debe contener una función que se llame `main`, que es la que ejecutará al comienzo de este (y luego puede llamar subsecuentemente a otras funciones).

Como editor pueden usar [Geany](https://www.geany.org/) o un editor más sencillo que ya esté instalado en el sistema, por ejemplo Gedit. Seguramente lo puedan encontrar en Menu → Editores, y cualquier otro editor también sirve.

### Acceder a la terminal

Al guardar el archivo, tendrán que fijarse en qué carpeta lo guardan, pues luego en la terminal deberán ubicarse en ese directorio.

Abran una Terminal, accesible desde Menú → Sistema o similar; puede que se llame “GNOME Terminal”, o “Consola”.

Para abrir una terminal también pueden usar el atajo del teclado CTRL + ALT + T, o con el boton derecho del mouse y `abrir terminal`.

Por omisión la terminal les deja ubicados en “/home/usuario” (por ejemlo “/home/ana” o “/home/martin”).

Luego, tendrán que ubicarse en el directorio donde está el archivo `.c`. Para esto se hace uso del comando `cd` (change directory), al cual le especificaremos en qué directorio nos queremos situar con la terminal.

Si su nombre de usuario es “ana”, lo mejor es que guarden en una carpeta con nombre bien corto, por ejemplo “/home/ana/tp0/hola.c” y luego en la terminal invoquen `cd /home/ana/tp0/`

### Compilación y Ejecución

Una vez hicieron eso, podrán compilar y ejecutar:

```cpp
gcc -o programa hola.c
./programa
```

La primera linea se refiere a la [compilación](compilacion-ejecucion.md), mientras que la segunda es la ejecución.

Si gcc emite algún error, deberán volver al editor y corregirlo. Una vez guardadas las correcciones, deberán volver a compilar el programa, ya que si no estarían ejecutando una versión vieja de este.
