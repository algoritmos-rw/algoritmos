---
title: Infraestructura
permalink: /infraestructura/
---

Infraestructura del curso
=========

Obviando la lista de correos, la plataforma más utilizada por el curso es [Github](http://github.com/), un sitio dedicado al hosting de repositorios de código (de Git). Estos repositorios contienen tanto el código mismo como su historial de versiones y cambios, mostrando claramente quién modificó qué linea de código, y permitiendo la contribución tanto de gente interna del curso como de gente externa a este, de manera facíl y accesible.

### Sitio Web

Este mismo sitio tiene su código libre y abierto en un repositorio: <https://github.com/algoritmos-rw/algo2>. Se puede ver todo el código html/css/js (utilizados en diseño web), cuándo fue cada archivo agregado y por quién. Que el código sea libre hace muy facil su contribución, ya que solo hace falta probar una idea nueva y proponerla, sin tener nada detrás de una caja negra.

En particular, este sitio utiliza un sistema llamado [Jekyll](https://jekyllrb.com/), un sistema especializado en convertir archivos de texto plano (por ejemplo, escritos en Markdown) a sitios web, permitiendo facilmente pasar de un conjunto de archivos escritos sin mucho conocimiento de diseño web a un sitio indexado y facil de navegar.

Como último comentario acerca de este sitio, Github provee la posibilidad de que si se tiene un repositorio de un sitio web estático[^1], este mismo te lo sirve en internet (es por eso que el dominio de este sitio es *github.io*).

### Corrector Automático

Dentro de [nuestra organización](https://github.com/algoritmos-rw/) en Github también se almacena, entre otras cosas, el [corrector automático](https://github.com/algoritmos-rw/corrector/tree/fiuba) (y control de copias).

El funcionamiento básico es:

* En un servidor externo se tiene constantemente corriendo el servicio 'fetchmail', que esta constantemente monitoreando la casilla de mails del corrector.

* Una vez que recibe un mail, por ejemplo uno con el sujeto 'TP1 - 100000 - Alumno', ya sabe que el trabajo a corregir es el TP1 del alumno de padron 100000.

* Con esos datos, se arma una máquina virtual en [Docker](https://hub.docker.com/r/algoritmosrw/corrector/), un sistema que tiene como fin el contener cada ejecución por separado en una máquina enteramente nueva y descartable. La idea principal del uso de Docker es que si, por ejemplo, se pudiese ver comprometido el trabajo práctico entregado, esto no vulnerabilizaría el servidor entero donde se tiene todo (sistema de entregas, consulta de notas, corrector), si no que solo se perjudica una máquina virtual externa.

* Allí se corren las pruebas del trabajo recibido y se devuelve el output del corrector

* Con el output del corrector ('Todo OK' o 'ERROR' más la salida de errores) se arma el mail de respuesta, y también se registra la entrega entera en un repositorio, al cual se le corre [MOSS](http://theory.stanford.edu/~aiken/moss/) un sistema de la universidad de Stanford que detecta copias entre códigos fuente.

* Finalmente, se envía el mail con la salida del corrector al alumno y al corrector individual designado.

### Sistema de Entregas

El último sistema relevante mantenido en Github es el del [sistema de entregas]({{site.entregas}}). En su [repositorio](https://github.com/algoritmos-rw/algo2_sistema_entregas) se puede ver el código en Python que, resumidamente, permite que el alumno no tenga que enviar un mail a la casilla de correos que el corrector automático monitorea constantemente; simplemente se ingresa el padrón y el trabajo correspondiente, y alrededor de esto se arma el correo que se envía. De ahí, el corrector automático levanta el mail recibido y comienza el proceso del corrector automático.

Para este proyecto se usa [Flask](https://palletsprojects.com/p/flask/), un framework fácil de usar que permite rápidamente hacer web-apps en Python.

### Consulta de Notas

También, se cuenta con un [equipo](http://bitbucket.org/fiuba7540) en [BitBucket](https://bitbucket.org/), otra plataforma análoga a Github donde se hostean repositorios de Git. Si bien de lo que respecta a Algoritmos II[^2] casi todo lo presente allí ya fue migrado a Github, por el momento [el sistema de consulta de notas]({{site.notas}}) sigue hosteado en un [repositorio](https://bitbucket.org/fiuba7540/consultar-notas/src/master/) de este sistema, también de codigo libre.

El funcionamiento de este sistema de consultas de notas es simplemente dado una planilla donde se especifican los padrones y mails (con los que se inscribieron a la lista de mails) de los alumnos, simplemente se verifica que los datos ingresados coincidan, y si lo hacen, se recibe un mail con un link para consultar las notas.

El código esta escrito en Python y nuevamente se usa Flask. La app esta diseñada de tal forma que pueda ser usada genéricamente tanto por un curso como por otro, ya que solo hay que específicar los parametros en un archivo externo.

[^1]: Un sitio web estático es aquel que no depende de bases de datos externas, por ejemplo un blog o cualquier sitio generado con Jekyll.
[^2]: El curso de [Algoritmos y Programación I]({{site.algo1}}) usa BitBucket como su plataforma principal.
