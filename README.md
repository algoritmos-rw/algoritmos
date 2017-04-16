Este es el repositorio de Algoritmos II.

Es un repo privado, que contiene la página web pública en el directorio [docs](docs). Por tanto, no se debe añadir material privado (como soluciones a los TPs).

La página web se publica en:

<https://algoritmos-rw.github.io/algo2/>


## Instrucciones para actualizar la página web

Cualquier commit en el directorio _docs_ se auto-publica en la página al hacer push a la rama _master_. GitHub se encarga de ese proceso.

Para visualizar los cambios de manera local, se debe instalar Jekyll. El archivo [Gemfile](docs/Gemfile) lo hace bastante fácil:

```
# Setup inicial

$ apt-get install bundler
$ git clone git@github.com:algoritmos-rw/algo2
$ cd algo2/docs
$ bundle install --path=../gems

# Para visualizar al editar

$ cd algo2/docs
$ bundle exec jekyll serve --livereload
```

(La opción `--livereload` es opcional, pero fuerza al navegador a mostrar
el nuevo contenido tras escribir un archivo.)
