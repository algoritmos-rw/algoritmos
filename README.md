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

Para todo tipo de TPs (incluyendo TDAs), es necesario crear un archivo de post dentro del directorio `_posts`. El nombre del archivo debe ser `YYYY-MM-DD-nombre.md`, como convención para todos los posts. El formato que debe tener un post de TP debe ser: 
```
---
layout: post
title: "Título entrega"
date: YYYY-MM-DD 13:00:00 -0300 (fecha de publicacion)

es_TP: True
nombre_TP: Nombre (e.g. Pila)
fin_cuatrimestre: YYYY-MM-DD
fecha_entrega: fecha
zip: nombre.zip
link_zip: Link del zip
link_enunciado: /tps/nombre-entrega
---

Contenido (que aparece en la página principal, en `Novedades`)
```

Para los TDAs, con solamente poner la información correspondiente, es suficiente (salvo alguna eventual actualización, o corrección del enunciado). Se puede encontrar el link al zip (y otros detalles) en posts de misma publicación de tp de cuatrimestres anteriores. 

Para el caso de TPs, es necesario crear el enunciado agregando el directorio `static/tps/cuatrimestre/tpX` (`X` sea 1, 2 o 3), y que dentro de éste haya un archivo `index.md` con el enunciado correspondiente. Después, hacer también el post. En caso de no tener algo para descargar desde la página de tps, se pueden obviar los campos `zip` y `link_zip`. Cualquier archivo adicional que quiera subirse para el tp (e.g. imágenes) debe hacerse dentro del directorio `assets/tps`. 

Con agregar el post, se actualiza automáticamente: 
- La sección de novedades, de la página principal (muestra las últimas 15 novedades).
- La página de TPs, que automáticamente obtiene todos los posts relacionados a tps (campo `es_TP`) para listarlos. Por este listado es importante el campo `fin_cuatrimestre`, ya que no muestra TPs cuya fecha de fin de cuatrimestre haya sido superada. Por lo tanto, la fecha a poner será el primero de agosto del corriente año, para el primer cuatrimestre, y el primero de enero o febrero del año siguiente para el segundo cuatrimestre. 

Además, es necesario habilitar la entrega en el sistema de entregas (de esto se encargan algunas personas con permisos).

## Actualizar página de docentes

Una vez que está por comenzar el cuatrimestre, es necesario actualizar la página de docentes con los que van a ser parte del curso. Para esto, lo único necesario es actualizar en el directorio `_data` el archivo `docentes.yml` con el nombre de cada docente, y el archivo de la foto. Mientras no se tenga una foto de algún corrector, se puede usar el archivo `assets/img/docentes/unknown.png`. 

## Subir nuevas encuestas

Para subir las encuestas de un cuatrimestre, subir el archivo dentro del directorio `assets/encuestas`, con nombre `YYYY-cuat.html`. Actualizar también la página de encuestas (`static/08_encuestas.md`).

