---
layout: page
title: Docentes
permalink: /docentes/
---

<table class="table table-borderless text-center">

  <tr>
    <td class="col-md-4"></td>
    <td class="col-md-4">
      <h2 class="hidden-xxs">Profesora</h2>
    </td>
    <td class="col-md-4"></td>
  </tr>

  <tr>
    <td></td>
    <td>
      <img src="../assets/img/docentes/rosita.jpg" title="Rosita Wachenchauzer" alt="Rosita Wachenchauzer" class="center-block img-rounded img-responsive">
      <span class="hidden-xxs">Rosita Wachenchauzer</span>
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
        <img src="{{site.baseurl}}{{ayudante.foto}}" title="{{ayudante.nombre}}" alt="{{ayudante.nombre}}" class="center-block img-rounded img-responsive" />
        <span class="hidden-xxs">{{ayudante.nombre}}</span>
    </td>
{% endfor %}
