---
layout: page
title: Infraestructura
permalink: /infraestructura/
---

Infraestructura del curso
=========

Obviando la lista de correos, la plataforma más utilizada por el curso es [Github](http://github.com/), un sitio dedicado al hosting de repositorios de código (de Git). Estos repositorios contienen tanto el código mismo como su historial de versiones y cambios, mostrando claramente quién modificó qué linea de código, y permitiendo la contribución tanto de gente interna del curso como de gente externa a este, de manera facíl y accesible.

Por ejemplo, este mismo sitio tiene su código libre y abierto en un repositorio: https://github.com/algoritmos-rw/algo2. Se puede ver todo el código html/css/js (utilizados en diseño web), cuándo fue cada archivo agregado y por quién. Que el código sea libre hace muy facil su contribución, ya que solo hace falta probar una idea nueva y proponerla, sin tener nada detrás de una caja negra. 

En particular, este sitio utiliza un sistema llamado [Jekyll](https://jekyllrb.com/), un sistema especializado en convertir archivos de texto plano (por ejemplo, escritos en Markdown) a sitios web, permitiendo facilmente pasar de un conjunto de archivos escritos sin mucho conocimiento de diseño web a un sitio indexado y facil de navegar. 

Por último, Github provee la posibilidad de que si se tiene un repositorio de un sitio web estático[^1], este mismo te lo sirve en internet (es por eso que el dominio de este sitio es *github.io*).

Dentro de [nuestra organización](https://github.com/algoritmos-rw/) en Github también se almacena, entre otras cosas, el [corrector automático](https://github.com/algoritmos-rw/corrector) (y control de copias).

El último sistema relevante mantenido en Github es el del [sistema de entregas]({{site.entregas}}). En su [repositorio](https://github.com/algoritmos-rw/algo2_sistema_entregas) se puede ver el código en Python que, resumidamente, permite que el alumno no tenga que enviar un mail a la casilla de correos que el corrector automático monitorea constantemente; simplemente se ingresa el padrón y el trabajo correspondiente, y alrededor de esto se arma el correo que se envía.

También, se cuenta con un [equipo](http://bitbucket.org/fiuba7540) en [BitBucket](https://bitbucket.org/), otra plataforma análoga a Github donde se hostean repositorios de Git. Si bien de lo que respecta a Algoritmos II[^2] casi todo lo presente allí ya fue migrado a Github, por el momento [el sistema de consulta de notas]({{site.notas}}) sigue hosteado en un [repositorio](https://bitbucket.org/fiuba7540/consultar-notas/src/master/) de este sistema, también de codigo libre.


[^1]: Un sitio web estático es aquel que no depende de bases de datos externas, por ejemplo un blog o cualquier sitio generado con Jekyll.
[^2]: El curso de [Algoritmos y Programación I]({{site.algo1}}) usa BitBucket como su plataforma principal.
