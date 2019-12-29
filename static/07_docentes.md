---
title: Docentes
permalink: /docentes/
---

<table class="table table-borderless text-center">

  <tr>
    <td class="col-md-4"></td>
    <td class="col-md-4">
      <h2 class="hidden-xxs">Profesor</h2>
    </td>
    <td class="col-md-4"></td>
  </tr>

  <tr>
    <td></td>
    {% assign profesor = site.data.docentes.profesor[0] %}
    <td>
        <div class='docente'>
          <img src="{{site.baseurl}}{{profesor.foto}}" title="{{profesor.nombre}}" alt="{{profesor.nombre}}" class="center-block img-rounded img-responsive docente-imagen" />
          <span class="hidden-xxs">{{profesor.nombre}}</span>
          <div class="docente-social">
            {%if profesor.mail%}<a href="mailto:{{profesor.mail}}" class="btn-social btn-outline social-link"><i class="fa fa-fw fa-envelope"></i></a>{%endif%}
            {%if profesor.github%}<a href="https://github.com/{{profesor.github}}" class="btn-social btn-outline social-link"><i class="fab fa-fw fa-github"></i></a>{%endif%}
          </div>
        </div>
    </td>
    <td></td>
  </tr>
  
  <tr>
    <td></td>
    <td>
      <h2 class="hidden-xxs">Ayudantes</h2>
    </td>
    <td></td>
  </tr>
  
{% for ayudante in site.data.docentes.ayudantes %}
    <p hidden>{% increment counter %}</p>
    {% assign mod = counter | minus:1 | modulo:3 %}
    {% if mod == 0 %}<tr>{% endif %}
    <td>
      <div class='docente'>
        <img src="{{site.baseurl}}{{ayudante.foto}}" title="{{ayudante.nombre}}" alt="{{ayudante.nombre}}" class="center-block img-rounded img-responsive docente-imagen" />
        <span class="hidden-xxs">{{ayudante.nombre}}</span>
        <div class="docente-social">
          {%if ayudante.mail%}<a href="mailto:{{ayudante.mail}}" class="btn-social btn-outline social-link"><i class="fa fa-fw fa-envelope"></i></a>{%endif%}
          {%if ayudante.github%}<a href="https://github.com/{{ayudante.github}}" class="btn-social btn-outline social-link"><i class="fab fa-fw fa-github"></i></a>{%endif%}
        </div>
      </div>
    </td>
{% endfor %}
