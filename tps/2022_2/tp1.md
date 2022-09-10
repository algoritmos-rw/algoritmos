---
math: true
---

{% assign tp = site.data.trabajos.TP1 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

# TP1: Manejo de archivos
{:.no_toc}

El trabajo práctico número 1 tiene fecha de entrega para el día **{{fecha}}**.
El objetivo de este trabajo práctico es el desarrollo que implique la utilización de los TDAs antes impleentados,
el diseño de nuevos TDAs necesarios para este desarrollo, y el uso de archivos y f flujo de entrada, salida y error. 


## Introducción

Se acercan las elecciones y no hay tiempo que perder. A pesar de las denuncias en su contra, el gobernador Pólez se 
postulará para su re-re-re-reelección. Como el actual sistema de votación está siendo cuestionado por denuncias de 
fraude, el gobernador Pólez ha coordinado la implementación del sistema de boleta única electrónica para darle 
credibilidad a los comicios venideros. También ha dispuesto otros cambios: en primer lugar, el transporte de las urnas 
se hará por *Empresa de correos Pólez e hijos*, la impresión de las nuevas boletas únicas la hará *Pólez calcográfica* 
y el sistema informático para el escrutinio lo desarrollará *Pólez Consulting*. 

En este contexto, nos han encargado la implantación de un componente del nuevo sistema de boleta única electrónica: 
la máquina de impresión de la boleta. Lamentablemente el gobernador Pólez se nos adelantó y ha encargado la fabricación 
de las máquinas (por licitación directa) al fabricante *Pólez hardware y asociados*, dejándonos el software que se 
ejecutará sobre la plataforma. Por esta razón, el programa respetará un protocolo de órdenes por entrada estándar 
(`stdin`).


## Consigna

Implementar en Go el sistema de gestión de votos que debe cumplir el siguiente protocolo.

## Protocolo

Este programa formará parte de un sistema automatizado. En lugar de presentar un menú con opciones en la pantalla, se 
esperará que el programa respete un protocolo de comunicación, en el cual se reciben comandos por la entrada estándar
(`stdin`). Cada comando recibido debe ser procesado y su resultado debe ser escrito en la salida estándar (`stdout`).
**Esto incluye mensajes de error**. Todo debe escribirse por la salida estándar. 

Cada línea de la entrada corresponde a un comando, y todos los comandos respetan un determinado formato. El formato 
estará compuesto del nombre del comando y sus parámetros, separados por espacios, en caso de requerirlos.

### Ejecución del programa

El programa debe ejecutarse de la siguiente forma:

  ```$ ./polez-soft ARCHIVO_LISTA ARCHIVO_PADRON```

Donde: 

* `ARCHIVO_LISTA`: Un archivo .csv donde están las respectivas boletas a votar. Cada línea representa un partido 
* político, que tiene nombre de dicho partido, nombre de el/la candidata a presidente, nombre de el/la candidata a 
* gobernador, y luego el del candidato a intendente. 
* `ARCHIVO_PADRON`: Un archivo .txt con los documentos habilitados a votar en la mesa. Este archivo tiene un documento 
* por línea. Cada documento escrito en formato numérico, sin puntos. 

Al empezar a ejecutar, el programa debe empezar a levantar los archivos y prepara la mesa electoral. 
Al terminar de preparar todo, debe imprimir por salida estándar (`stdout`) lo que corresponda a la salida según el 
estado.

#### Salida

- `OK`: si no se produjeron errores.
- `ERROR1`: si hubo un error en la lectura de los archivos (o archivos inexistentes, o sin permisos)
- `ERROR2`: si faltó alguno de los parámetros


#### Ejemplo:

```
./polez-soft lista_candidatos.csv padron-que-no-existe.csv
ERROR1
./polez-soft lista_candidatos.csv -->le falta el otro archivo
ERROR2
./polez-soft lista_candidatos.csv padron.csv
OK 
```

En caso de errores, el programa debe terminar su ejecución. 

### Comando: `ingresar`

#### Formato

```ingresar <NumeroDNI>```

#### Descripción: 

El votante ingresa este comando al momento de entrar en la fila de personas esperando a usar la máquina.

#### Parámetros

- NumeroDNI: Un número entero positivo mayor a 0 que representa el número de documento del votante.

#### Salida

- `OK`: si no se produjeron errores.
- `ERROR3`: si el número de DNI es menor o igual a 0.

En este comando **no** se valida si el dni se encuentra en el padrón electoral (eso sucederá en el siguiente comando).
En caso de error, simplemente esperar por un nuevo ingresa de un comando. 

#### Ejemplo:

```
ingresar 36109000
OK 
ingresar 40100900
OK
ingresar -12345678
ERROR3
ingresar 123
OK
```

Si por el caso el DNI 123 no se encontrara en el padrón, igualmente se imprime OK y se agrega a la fila.

### Comando: `votar`

#### Formato

```votar <NumeroLista> <TIPO-VOTO>```

#### Descripción

Este comando se utiliza para votar por alguna alternativa. Para simplicidad y evitar que alguien escriba mal el nombre 
de un partido político, se decidió que los votantes ingresen su número de lista. El número de lista es directamente el 
número de línea dentro del archivo de partidos que ocupa cada partido.

#### Parámetros

Puede llevar 2 tipos de parámetros:

* El `TIPO-VOTO`, que puede ser `Presidente`, `Gobernador` o `Intendente`.
* El número de lista, explicado anteriormente. 

Una persona puede votar por diferentes partidos políticos para Gobernador y Presidente, por ejemplo. 
Al mismo tiempo, si alguien decidiera votar primero para Presidente por un partido, y luego decide cambiar de opinión y 
votar nuevo para Presidente para otro partido, se sobreescribirá el voto por la nueva alternativa. A cambio, considerar 
el siguiente comando (`deshacer`). 

El número de lista 0 está reservado para impugnar el voto (equivalente a dejar una feta de salame en el sobre). En caso 
de impugnarse el voto, se impugna completo, no para un partido en particular. El votante puede seguir efectuando votos 
(sería meter boletas en el mismo sobre), pero ninguno de estos contará. Para des-impugnar el voto, se debe haber 
deshecho esa operación (nuevamente, ver comando `deshacer`, más adelante).

#### Salida

- `OK`: si no se produjeron errores. 
- `ERROR4`: si el DNI de la persona votando no se encuentra en el padrón de la mesa actual. Este error también se 
   produce si no hay nadie esperando para votar. 
- `ERROR5`: si el DNI de la persona votando **ya emitió y finalizó su voto** (ver `fin-votar`). 
- `ERROR6`: si el número de lista es incorrecto (no es una opción válida).
- `ERROR7`: si el tipo de voto no es uno de los enunciados anteriormente.

En caso de producirse el Error 4, se descarta el padrón de la fila. 
En caso de los demás errores, simplemente se espera por otro ingreso que sea correcto. 

#### Ejemplo: 

```
ingresar 30000000
OK
ingresar 16000000
OK
ingresar 123
OK
votar 1 Presidente
OK
votar 5 Intendente
OK
votar 8 Gobernador
ERROR6
votar 5 Presi
ERROR7
votar 4 Gobernador
OK
votar 2 Presidente
```

El estado del voto del votante con DNI 30.000.000 hasta aquí sería: 
```
Presidente: Lista 2
Gobernador: Lista 4
Intentente: Lista 5
```


### Comando: `deshacer`

#### Formato 

```deshacer```

#### Descripción 

Deshace la última operación de voto del votante actual. Es decir, ningún voto ya finalizado (ver siguiente comando) puede verse alterado por la aplicación de este comando. 
El voto completo del votante actual queda en el estado exactamente anterior a la última utilización del comando `votar`. 

#### Parámetros

Ninguno. 

#### Salida

- `OK`: si no se produjo ningún error. 
- `ERROR8`: si no hay nadie esperando votar, o no hay nada que deshacer (el votante actual aún no realizó votaciones, o todas sus votaciones fueron ya deshechas).

#### Ejemplo:

Siguiendo con el ejemplo anterior: 
```
deshacer
```

El estado actual del voto del votante con DNI 30.000.000 será:
```
Presidente: Lista 1
Gobernador: Lista 4
Intentente: Lista 5
```
La operación que se deshizo fue la de haber votado para presidente a lista 2. 

### Comando: `fin-votar`

#### Formato

```fin-votar```

#### Descripción

Termina el proceso de votación para el votante actual en la fila. Se emite su voto completo, considerando su 
alternativa elegida para Presidente, Gobernador e Intendente. Si no eligió alguna alternativa para uno o más tipos, se 
contarán como votos en blanco. 

Al finalizar el voto, se añadirán al conteo de las alternativas electas para Presidente, Gobernador e Intendente 
correspondientes, incluyendo el voto en blanco. En caso de haberse impugnado el voto, no se contará para ninguna, y 
simplemente se irá a un conteo de votos impugnados.

#### Parámetros

Ninguno. 

#### Salida

- `OK`: si no se produjo ningún error. 
- `ERROR9`: si no había nadie en la fila para votar.

#### Ejemplo: 

Continuando el ejemplo anterior: 
```
deshacer 
fin-votar
```

El voto finalmente emitido será:
```
Presidente: Lista 1
Gobernador: Voto en Blanco
Intentente: Lista 5
```


### Fin de ejecución del programa

Una vez que se hubiera terminado el ingreso por entrada estándar (es decir, `stdin` finalizó), se debe imprimir el 
resultado de los comisiones para esta mesa con el formato mostrado a continuación. En caso de haber alguien 
"a medio votar", así como otros votantes en la fila esperando, se deberá imprimir `ERROR10` y se descartarán sus votos, 
considerando que no cumplieron con su deber civil yendo a votar los últimos 15 minutos. De ser posible, se les cobrará 
la correspondiente multa allí mismo, pero esto queda fuera del alcance del trabajo práctico. Esto será llevado a cabo
por *Pólez Cobraciones SRL*.

### Salida

```
Presidente: 
<nombre del partido 1> - Postulante: X votos
<nombre del partido 2> - Postulante: Y votos
...
Votos en Blanco: Z votos

Gobernador: 
<nombre del partido 1> - Postulante: X2 votos
<nombre del partido 2> - Postulante: Y2 votos
...
Votos en Blanco: Z2 votos

Intendente:
<nombre del partido 1> - Postulante: X3 votos
<nombre del partido 2> - Postulante: Y3 votos
...
Votos en Blanco: Z3 votos

Votos impugnados: W votos
```


## Ejemplo integrador:

Para este ejemplo integrador, que el archivo de boletas es: 
```
Frente para la Derrota,Alan Información,Ignacio Líneas,Esteban Federico
Pre,Jesús Sintasi,Javier Colisión,Yennifer Woolite
++A,Ignacio Gundersen,Emisor Bello,Daniela Peligro
```
Y el Padrón electoral es el siguiente:
```
12345678
98765432
10000000
99999999
```

El ejemplo:
```
ingresar 12345678
OK
ingresar  123
OK
ingresar 123a
ERROR3
ingresar 12345678
OK
ingresar 98765432
OK
ingresar 10000000
OK
votar 1 Presidente
OK
votar 4 Presidente
ERROR6
votar 3 Gobernador
OK
votar 1 Intendente
OK
votar 3 Intendente
deshacer
OK
votar 1 RectorDeLaUBA
ERROR7
fin-votar
OK
votar 1 Presidente
ERROR4
votar 1 Presidente
ERROR5
deshacer
ERROR8
votar 0 Presidente
OK
deshacer
OK
votar 3 Presidente
OK
votar 3 Gobernador
OK
votar 3 Intendente
OK
fin-votar
OK
fin-votar
OK
votar 1 Presidente
ERROR4
fin-votar
ERROR9
```

Al terminar el programa, la salida final sería la siguiente: 
```
Presidente: 
Frente para la Derrota - Alan Informaión: 1 voto
Pre - Jesús Sintasi: 0 votos
++A - Ignacio Gundersen: 1 voto
Votos en Blanco: 1 voto

Gobernador:
Frente para la Derrota - Ignacio Líneas: 0 votos
Pre - Javier Colsión: 0 votos
++A - Emisor Bello: 2 votos
Votos en Blanco: 1 voto

Intendente:
Frente para la Derrota - Esteban Federico: 1 voto
Pre - Yennifer Woolite: 0 votos
++A - Daniela Peligro: 1 voto
Votos en Blanco: 1 voto

Votos impugnados: 0 votos
```

## Archivos provistos por el curso

Como se menciona anteriormente, este trabajo práctico tiene como objetivo tanto la utilización de TDAs previamente 
implementados, así como diseñar nuevos. En este caso, como primera incursión, les proveemos nosotros de un diseño s
ugerido par implementar, con un TDA `Votante`, un `struct Voto` (que no es un TDA), y un TDA `Partido`. Proveemos 
también la firma de las primitivas/métodos, pero sin una implementación. Esta deberían completarla ustedes. El objetivo 
de esto es guiarlos a implementar un buen diseño. Pueden modificar el diseño propuesto como a ustedes mejor les parezca.
En futuros TPs no se les dará diseño alguno, y esperaremos que diseñen correctamente, implementando los TDAs que les 
parezca correctos según la necesidad. 


Aparte de esto, les brindaremos unos archivos que funcionarán de prueba. Estos **no** son como las pruebas anteriores 
que vinieron ejecutando, sino que serán pruebas de Input/Output (IO, o entrada/salida). Para ejecutar dichas pruebas, 
deben descomprimir el archivo de pruebas y, previa compilación del código del TP mediante, ejecutar (estando parados en 
el directorio donde se encuentren las pruebas):

```
$ ./pruebas.sh <RUTA_AL_EJECUTABLE_TP>
```

Donde `RUTA_AL_EJECUTABLE_TP` es la ruta del ejecutable que hayan conseguido tras la compilación de su código. La ruta 
puede ser relativa al directorio actual, o absoluta. 

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

  - El código implementado específicamente para la implementación de este TP.

  - Cualquier otro código que fuera necesario. Aclaración: en caso de utilizar 
  código de TDAs implementados, y evitar tener que copiar y pegar dicho código
  dentro de la carpeta para que ejecute correctamente, se recomienda fuertemente
  leer [el FAQ sobre enlaces simbólicos](faq/symlink.md).

  - un archivo _go.mod_ que permita compilar y ejecutar el módulo en cuestión. 
  El nombre del módulo debería ser _rerepolez_. 


La entrega se realiza únicamente en forma digital a través del [sistema de
entregas]({{site.entregas}}), con todos los archivos mencionados en un único
archivo ZIP.
