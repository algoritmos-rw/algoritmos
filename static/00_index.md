---
layout: home
permalink: /
---

# Inicio

  <p>
    Este es el sitio de la materia <strong>Algoritmos y Programación II</strong>, 
    curso <strong>Buchwald</strong> (ex <strong>Wachenchauzer</strong>), de FIUBA.
  </p>

  <p>
    En caso de encontrar algún problema con la página (desde errores de fechas, links rotos, falta publicar algún trabajo, o lo que fuere), por favor crear un issue en <a href="https://github.com/algoritmos-rw/algo2/issues">la página de issues del repositorio</a>.
  </p>

  <h3 class="page-heading">Novedades</h3>
  
  <ul class="post-list">
	{% for post in site.posts limit:15 %}
	  <li>
      <a class="post-link" href="{{ post.url | relative_url }}">
        <span class="post-meta">{{ post.date | date: "%d/%m/%Y" }}</span>
      </a>
      &ndash; 
      <p class="post-excerpt">{{ post.excerpt | remove: '<p>' | remove: '</p>' }}</p>
	  </li>
	{% endfor %}
  </ul>

  <p>Suscribirse con <a href="{{ '/feed.xml' | relative_url }}" class="rss-subscribe">RSS</a>.</p>


