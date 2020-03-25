# Algo2

Este es el repositorio del sitio web de Algoritmos y Programación II, publicado en:

<https://algoritmos-rw.github.io/algo2/>

## Instrucciones para actualizar la página web

Cualquier commit en el directorio raíz se auto-publica en la página al hacer push a la rama _master_. GitHub se encarga de ese proceso.

Para visualizar los cambios de manera local, se debe instalar [Jekyll](https://jekyllrb.com/docs/installation/#ubuntu). El archivo [Gemfile](Gemfile) lo hace bastante fácil:

```
# Setup inicial

$ apt-get install ruby ruby-dev bundler
$ gem install jekyll bundler
$ git clone git@github.com:algoritmos-rw/algo2
$ cd algo2
$ bundle install --path=../gems
$ // de tener problemas con nokogiri: apt-get install libxml2-dev

# Para visualizar al editar

$ cd algo2
$ bundle exec jekyll serve --livereload
$ // de tener problemas con javascript runtime: apt-get install nodejs

```

(La opción `--livereload` es opcional, pero fuerza al navegador a mostrar
el nuevo contenido tras escribir un archivo.)

## Cómo realizar la publicación de un TP

Al principio del cuatrimestre actualizar el archivo `_data/trabajos.yml` y `_data/cuatrimestre.yml` para reflejar las nuevas fechas de publicación y entrega y de fin de cuatrimestre.

Para el caso de TPs, es necesario crear el enunciado agregando el directorio `static/tps/cuatrimestre/tpX` (`X` sea 1, 2 o 3), y que dentro de éste haya un archivo `index.md` con el enunciado correspondiente. Después, hacer también el post. Cualquier archivo adicional que quiera subirse para el tp (e.g. imágenes) debe hacerse dentro del directorio `assets/tps`.

Además, es necesario habilitar la entrega en el sistema de entregas (de esto se encargan algunas personas con permisos).

## Actualizar página de docentes

Una vez que está por comenzar el cuatrimestre, es necesario actualizar la página de docentes con los que van a ser parte del curso. Para esto, lo único necesario es actualizar en el directorio `_data` el archivo `docentes.yml` con el nombre de cada docente, y el archivo de la foto. Mientras no se tenga una foto de algún corrector, se puede usar el archivo `assets/img/docentes/unknown.png`.

## Subir nuevas encuestas

Para subir las encuestas de un cuatrimestre, subir el archivo dentro del directorio `assets/encuestas`, con nombre `YYYY-cuat.html`. Actualizar también la página de encuestas (`static/08_encuestas.md`).
