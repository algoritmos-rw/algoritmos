# FAQ - Entorno de Desarollo
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo hago para instalar el entorno de desarrollo en mi PC?

Hay varias opciones, según tu sistema operativo y tus preferencias. Para poder hacer los ejercicios y TPs de este curso necesitás tener funcionando en tu PC los siguientes programas:

*   compilador C: **GCC** (y opcionalmente **clang**)
*   **GNU make**
*   **Valgrind**
*   **Python** (opcional, para el último TP)

Además es altamente recomendado contar con un **editor de texto** o un **entorno de desarrollo (IDE)** que permita programar y compilar cómodamente. Algunas posibilidades son:

*   [Geany](http://www.geany.org/), un entorno de desarrollo amigable, multi plataforma.
*   [Codeblocks](http://www.codeblocks.org/), otro entorno integrado de desarrollo, para Windows, Mac OS y Linux.

## Instalar Linux

Todas las herramientas mencionadas son multiplataforma, lo que significa que pueden ser utilizadas en cualquier sistema operativo. Todas... salvo una: Valgrind. Lamentablemente **Valgrind no funciona sobre Windows** (existen algunos sustitutos, pero como en este curso utilizamos Valgrind para corregir los trabajos prácticos, es recomendable que también uses Valgrind). Para Mac OS X existe una versión pero aún no es estable. Esto significa que nuestra única opción es **Linux**.

Existen muchas distribuciones de Linux, y cada una se configura de manera diferente. Una de las distribuciones más populares hoy en día es **Ubuntu**, y es la que explicamos en esta guía. Si ya tenés Ubuntu instalado, podés saltear al paso de instalación de las herramientas.

## ¡Pero quiero seguir usando Windows!

Si actualmente tenés Windows, básicamente tenés tres opciones para instalar Linux en tu PC:

1.  Linux como único sistema operativo (**chau Windows**).
1.  Linux **al lado de Windows** (esta opción se conoce como **_dual boot_**).
1.  Linux **dentro de Windows**, corriendo dentro de una **máquina virtual**.

Si no querés borrar Windows, la opción 3 suele ser la más fácil y es la que se explica a continuación.

## Virtualbox + Ubuntu

Virtualbox es el software de virtualización (es decir, que permite ejecutar una máquina virtual) recomendado. A grandes resgos, los pasos necesarios para llevar a cabo la instalación son:

1.  [Instalar Virtualbox](http://www.virtualbox.org/wiki/Downloads) en Windows.
1.  Utilizando Virtualbox, crear una máquina virtual. Recomendamos asignar al menos 4 GB de disco y 512 MB de memoria RAM.
1.  [Bajar la ISO de Ubuntu](http://www.ubuntu.com/getubuntu/download) de 32 bits.
1.  Arrancar la máquina virtual con la ISO asignada a la lectora de CD.
1.  Seguir los pasos de instalación de Ubuntu.
1.  (Opcional) Instalar los _Guest Additions_ de Virtualbox dentro de Ubuntu ([explicado acá](http://reciclado100.blogspot.com.ar/2009/02/como-instalar-guest-additions.html) en español o [acá](http://helpdeskgeek.com/linux-tips/install-virtualbox-guest-additions-in-ubuntu/) en inglés).
1.  Instalar dentro de Ubuntu las herramientas necesarias para el curso (explicado más adelante).

Los pasos 1 a 5 están explicados en detalle en cualquiera de las siguientes guías:

*   [Guía en español](http://www.arturogoga.com/2008/02/19/linux-en-windows-con-virtual-box-ubuntu/)
*   [Guía en inglés](http://www.psychocats.net/ubuntu/virtualbox) (más reciente que las otras)
*   [Otra guía en inglés](http://aruljohn.com/info/virtualbox/)

El último paso se explica a continuación.

## Instalar las heramientas de desarrollo en Ubuntu

Abrir una terminal (CTRL+ALT+T) y escribir lo siguiente:

`sudo apt-get install build-essential valgrind manpages-dev gdb`

Te va a pedir la contraseña de usuario. Una vez ingresada, se bajarán de internet e instalarán automáticamente todas las herramientas. ¡Ya está!

Estas herramientas son:

* [build-essential](https://packages.ubuntu.com/bionic/build-essential): Herramientas esenciales de toda distribución de Linux. Lo que mas usaremos es gcc (compilador de C) y make (herramienta para automatización de compilaciones).
* [Valgrind](http://valgrind.org/): Herramienta para verificar el uso de memoria del programa, como ver si hay perdidas de memoria.
* [manpages-dev](http://man7.org/linux/man-pages/man1/intro.1.html): Manual de usuario de Linux. Extremadamente util para tener la documentación oficial de los comandos utilizados. Se invoca con el comando `man`. Por ejemplo, `man printf`
* [gdb](https://www.gnu.org/software/gdb/): Herramienta para la depuración de programas.

Finalmente, se recomienda instalar un editor de texto más potente que los que vienen por defecto. Algunos ejemplos son [Geany](https://www.geany.org/) (`sudo apt-get install geany`), [Atom](https://atom.io/) y [Visual Studio Code](https://code.visualstudio.com/).
