Este es el repositorio del sitio web de Algoritmos y Programación II, publicado en:

<https://algoritmos-rw.github.io/algo2/>

y redireccionada desde:

<https://algoritmos7541-rw.tk/>

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
