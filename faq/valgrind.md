# FAQ - Errores de Valgrind
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo hago para que Valgrind me indique la línea en la que hay un error?

Es necesario agregar la opción `-g` (debug) a la línea de compilación. Eso le dice al compilador que incluya la información de debugging en el binario, que despues Valgrind usa para saber en qué línea están las instrucciones.

Además, la opción `--track-origins=yes` sirve para llevar un registro del uso de valores sin inicializar que pueden llegar a estar trayendo problemas.

## ¿Qué significa Conditional jump or move depends on uninitialised value?

Significa que una variable utilizada en algún salto condicional (por ejemplo, `if`) no está inicializada. Puede ser que se trate de una variable local que no se asignó a nada, o de una variable que otra función debía guardar, y por algún motivo no la guardó.

## ¿Qué significa Invalid read of size X / Invalid write of size X?

Este tipo de mensajes suele aparecer cuando se trata de leer o escribir más posiciones de las que fueron reservadar originalmente. Por ejemplo si se hizo:

``` cpp
void** datos = malloc(10 * sizeof(void*));
```

Despues se podrá leer y escribir hasta `datos[9]`, al acceder a `datos[10]` o mayor, dará este error.

## Al ejecutar un programa dentro de Valgrind sucede algo distinto que sin él, ¿cómo puede ser?

Puede pasar que dentro de Valgrind falle y fuera de este no, o al revés.  Ambas situaciones son medianamente normales.

Esto se debe a que para poder verificar que no haya pérdidas de memoria, Valgrind maneja la memoria diferente que como se maneja normalmente.  Es por eso que es algo más o menos común que cuando se ejecuta un programa con problemas dentro de Valgrind no se comporte exactamente igual que fuera de Valgrind.

Solucionando los problemas de memoria que tenga el programa se debería obtener el mismo comportamiento tanto dentro como fuera de Valgrind.
