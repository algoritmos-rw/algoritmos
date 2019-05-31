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
    En caso de encontrar algún problema con la página (desde errores de fechas, links rotos, falta publicar algún trabajo, o lo que fuere), por favor crear un issue en <a href="{{site.github.repository_url}}/issues">la página de issues del repositorio</a>.
  </p>

  <h3 class="page-heading">Novedades</h3>

  <ul class="post-list">
  {% assign inicio_cuatrimestre = site.data.cuatrimestre.inicio_cuatrimestre | date: "%s" %}

	{% for post in site.posts limit:15 %}

    {% assign date = post.date | date: "%s" %}
    {% if date < inicio_cuatrimestre %}
      {% continue %}
    {% endif %}
	  <li>
      <a class="post-link" href="{{ post.url | relative_url }}">
        <span class="post-meta">{{ post.date | date: "%d/%m/%Y" }}</span>
      </a>
      &ndash; 
      <p class="post-excerpt">{{ post.excerpt | remove: '<p>' | remove: '</p>' }}</p>
	  </li>
	{% endfor %}
  </ul>

  <div id="embedded-calendario">
    <h3 class="page-heading">Información sobre próximas clases</h3>
    <p>
      Recomendamos revisar el <a href="{{site.data.cuatrimestre.calendario_detallado}}">calendario detallado</a> 
      de la materia.
    </p>
  </div>

  <div id='calendario'>
    <h3 class="page-heading">Próximas fechas importantes</h3>
    <table class="table table-striped">
      <tbody id="tabla-calendario">
        <tr>
          <td><strong>Día</strong></td>
          <td><strong>Fecha</strong></td>
          <td><strong>Detalle</strong></td>
        </tr>
      </tbody>
    </table>
  </div>

  <script src="{{ '/assets/js/calendario.js' | relative_url }}"></script>
  <script src="{{ '/assets/js/index.js' | relative_url }}"></script>