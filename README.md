Este es el repositorio del sitio web de Algoritmos y Programación II, publicado en:

<https://algoritmos-rw.github.io/algo2/>

## Instrucciones para actualizar la página web

Cualquier commit en el directorio raíz se auto-publica en la página al hacer push a la rama _master_. GitHub se encarga de ese proceso.

Para visualizar los cambios de manera local, se debe instalar Jekyll. El archivo [Gemfile](Gemfile) lo hace bastante fácil:

```
# Setup inicial

$ apt-get install bundler
$ git clone git@github.com:algoritmos-rw/algo2
$ cd algo2
$ bundle install --path=../gems

# Para visualizar al editar

$ cd algo2
$ bundle exec jekyll serve --livereload
```

(La opción `--livereload` es opcional, pero fuerza al navegador a mostrar
el nuevo contenido tras escribir un archivo.)

## Cómo realizar la publicación de un TP

Al principio del cuatrimestre actualizar el archivo `_data/trabajos.yml` para reflejar las nuevas fechas de publicación y entrega.

Para todo tipo de TPs (incluyendo TDAs), es necesario crear un archivo de post dentro del directorio `_posts`. El nombre del archivo debe ser `YYYY-MM-DD-publicacion-trabajo.md`, como convención para todos los posts. El formato que debe tener un post de TP debe ser, con el ejemplo de la publicación de cola: 
```
---
layout: post
title: "Publicado TDA Cola"
date: 2018-04-07 15:00:00 -0300

trabajo: 'Cola'
---
{% for tp in site.data.trabajos.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
```

Solo deben modificarse las primeras 3 lineas. El resto es magia de Liquid. Por último, fijarse en `_data/trabajos.yml` que los datos esten al día.

Para el caso de TPs, es necesario crear el enunciado agregando el directorio `static/tps/cuatrimestre/tpX` (`X` sea 1, 2 o 3), y que dentro de éste haya un archivo `index.md` con el enunciado correspondiente. Después, hacer también el post. Cualquier archivo adicional que quiera subirse para el tp (e.g. imágenes) debe hacerse dentro del directorio `assets/tps`. 

Con agregar el post, se actualiza automáticamente: 
- La sección de novedades, de la página principal (muestra las últimas 15 novedades).
- La página de TPs, que automáticamente obtiene todos los posts relacionados a tps para listarlos. 

Además, es necesario habilitar la entrega en el sistema de entregas (de esto se encargan algunas personas con permisos).

## Actualizar página de docentes

Una vez que está por comenzar el cuatrimestre, es necesario actualizar la página de docentes con los que van a ser parte del curso. Para esto, lo único necesario es actualizar en el directorio `_data` el archivo `docentes.yml` con el nombre de cada docente, y el archivo de la foto. Mientras no se tenga una foto de algún corrector, se puede usar el archivo `assets/img/docentes/unknown.png`. 

## Subir nuevas encuestas

Para subir las encuestas de un cuatrimestre, subir el archivo dentro del directorio `assets/encuestas`, con nombre `YYYY-cuat.html`. Actualizar también la página de encuestas (`static/08_encuestas.md`).

