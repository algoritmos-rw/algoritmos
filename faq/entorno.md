# FAQ - Entorno de Desarollo
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo hago para instalar el entorno de desarrollo en mi PC?

Hay varias opciones, según tu sistema operativo y tus preferencias. Para poder hacer los ejercicios y TPs de este curso necesitás tener funcionando en tu PC los siguientes programas:

*   **Compilador Golang**
*   **GNU make**
*   **Python** (opcional, para el último TP)

Además es altamente recomendado contar con un **editor de texto** o un **entorno de desarrollo (IDE)** que permita programar y compilar cómodamente. Algunas posibilidades son:

* [Goland](https://www.jetbrains.com/go/download/) (se obtiene licencia gratuita con el mail FIUBA). 
* [Visual Studio Code](https://code.visualstudio.com/), con la extensión para Go.
* [Sublime Text](https://www.sublimetext.com/), otro entorno de desarrollo. 
* [Geany](http://www.geany.org/), un entorno de desarrollo amigable, multi plataforma.

## Instalar Linux

Para la cursada es **obligatorio** el uso de un entorno UNIX durante todo el cuatrimestre. Puede utilizarse cualquier distribución de Linux. 

Existen muchas distribuciones de Linux, y cada una se configura de manera diferente. Una de las distribuciones más populares hoy en día es **Ubuntu**, y es la que explicamos en esta guía. Si ya tenés Ubuntu instalado, podés saltear al paso de instalación de las herramientas.

## ¡Pero quiero seguir usando Windows!

Si actualmente tenés Windows, básicamente tenés tres opciones para instalar Linux en tu PC:

1.  Linux como único sistema operativo (**chau Windows**).
1.  Linux **al lado de Windows** (esta opción se conoce como **_dual boot_**).
1.  Linux **dentro de Windows**, corriendo dentro de una **máquina virtual**.

Si no querés borrar Windows, la opción 3 suele ser la más fácil y es la que se explica a continuación. Igualmente, para usuarios de Windows recomendamos la opción 2 ya que tendrá mejor rendimiento. Para esta materia puede que estén bien con una máquina virtual, pero para materias futuras igualmente necesitarán tenerlo instalado de todas formas. 

Dejamos [aquí un link a guías de instalación del LUGFi](https://cloud.disroot.org/s/Wc7oMSo4jHg9Wq9) ([link alternativo en caso de fallas](https://drive.google.com/file/d/1Nj4NdHQSJGzq5sNexKBBSN--1Qni_lYQ/view?usp=sharing)). También recomendamos consultarles a ellos en su [grupo de Facebook](https://www.facebook.com/groups/lugfi) ante cualquier duda (así como en la lista de consultas del curso).

## Virtualbox + Ubuntu

Virtualbox es el software de virtualización (es decir, que permite ejecutar una máquina virtual) recomendado. A grandes resgos, los pasos necesarios para llevar a cabo la instalación son:

1.  [Instalar Virtualbox](http://www.virtualbox.org/wiki/Downloads) en Windows.
1.  Utilizando Virtualbox, crear una máquina virtual. Recomendamos asignar al menos 4 GB de disco y 512 MB de memoria RAM.
1.  [Bajar la ISO de Ubuntu Desktop](https://ubuntu.com/download/desktop) “LTS” de 64 bits.[^no32]
1.  Arrancar la máquina virtual con la ISO asignada a la lectora de CD.
1.  Seguir los pasos de instalación de Ubuntu.
1.  (Opcional) Instalar los _Guest Additions_ de Virtualbox dentro de Ubuntu ([explicado acá](http://reciclado100.blogspot.com.ar/2009/02/como-instalar-guest-additions.html) en español o [acá](http://helpdeskgeek.com/linux-tips/install-virtualbox-guest-additions-in-ubuntu/) en inglés).
1.  Instalar dentro de Ubuntu las herramientas necesarias para el curso (explicado más adelante).

Los pasos 1 a 5 están explicados en detalle en cualquiera de las siguientes guías:

*   [Guía en español](http://www.arturogoga.com/2008/02/19/linux-en-windows-con-virtual-box-ubuntu/)
*   [Guía en inglés](http://www.psychocats.net/ubuntu/virtualbox) (más reciente que las otras)
*   [Otra guía en inglés](http://aruljohn.com/info/virtualbox/)

El último paso se explica a continuación.

[^no32]: Si la máquina o el sistema operativo Windows donde se realiza la instalación es de 32 bits, no se puede usar Ubuntu, pero sí [Xubuntu LTS 18.04](https://xubuntu.org/download/).

## Instalar las heramientas de desarrollo en Ubuntu

Abrir una terminal (CTRL+ALT+T) y escribir lo siguiente:

```
	sudo apt-get update
	sudo apt install build-essential valgrind manpages-dev gdb
```
Les va a pedir la contraseña de usuario. Una vez ingresada, se bajarán de internet e instalarán automáticamente todas las herramientas auxiliares.

Se puede instalar el compilador de Go utilizando el comando `sudo apt-get install golang-go`. Ejecutar dicho comando y validar la versión de go ejecutando el comando `go version`. Si efectivamente se trata de la versión 1.22 (puede ser 1.22.0, o cualquier número al final), entonces ya está. A veces este comando no instala la última versión, sino una anterior. Si tuvieran instalada una versión posterior (por ejemplo, 1.21.6) no debería haber ningún problema. Lo importante es que sea al menos 1.22. 
Para instalar el compilador del lenguaje con la versión exacta que estamos utilizando en el curso, pueden seguir los siguientes comandos: 
```
	sudo apt remove --autoremove golang
	sudo rm -rf /usr/local/go
	sudo apt-get install wget
	wget https://go.dev/dl/go1.22.0.linux-amd64.tar.gz
	sudo tar -xvf go1.22.0.linux-amd64.tar.gz
	sudo mv go /usr/local
	rm go1.20.13.linux-amd64.tar.gz
```

Luego, modificar el archivo `~/.profile` o `~/.bash_profile` (según cuál exista) agregando las siguientes líneas al final del mismo:
```
	export GOROOT=/usr/local/go
	export GOPATH=$HOME/Projects
	export PATH=$GOPATH/bin:$GOROOT/bin:$PATH 
```

Reiniciar la terminal para que tome los últimos cambios. Abrir una nueva y ejecutar el comando `go version` para validar que el compilador se encuentre instalado correctamente y con la versión esperada. 


{% include footnotes.html %}
