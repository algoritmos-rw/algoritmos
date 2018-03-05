---
layout: home
permalink: /
---

# Inicio

  <p>
    Este es el sitio de la materia <strong>Algoritmos y Programación II</strong>, 
    curso <strong>Buchwald</strong> (ex <strong>Wachenchauzer</strong>), de FIUBA.
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


