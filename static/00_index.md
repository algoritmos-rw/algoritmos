---
layout: home
permalink: /
---

# Inicio

  <p>
    Este es el sitio de la materia <strong>Algoritmos y Programación II</strong>, 
    curso <strong>Wachenchauzer</strong>, de FIUBA.
  </p>

  <h3 class="page-heading">Trabajos Prácticos</h3>
  
  <ul class="post-list">
	{% for tp in site.data.tps %}{% if tp.is_publicado %}
	  <li>
        <span class="post-meta">{{ tp.fecha_publicacion }}</span>
      &ndash;
        <p class="post-excerpt"> Publicado el 
        <a class="post-link" href="{{ tp.link_enunciado | relative_url }}">
        <span class="post-meta">{{tp.nombre}}</span>
        </a>
        </p>
	  </li>
	{%endif%}{% endfor %}
  </ul>

  <h3 class="page-heading">Novedades</h3>
  
  <ul class="post-list">
	{% for post in site.posts %}
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


