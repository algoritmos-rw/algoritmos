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
      <img src="../assets/img/docentes/Rosita Wachenchauzer.jpg" title="Rosita Wachenchauzer" alt="Rosita Wachenchauzer" class="center-block img-rounded img-responsive">
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
  
{% for image in site.static_files %}
    {% if image.path contains "docentes" %}
    {% unless image.path contains "Rosita" %} 
        <p hidden>{% increment counter %}</p>
        {% assign mod = counter | minus:1 | modulo:3 %}
        {% if mod == 0 %}
            <tr>
        {% endif %}
        <td>
            <img src="{{site.baseurl}}{{image.path}}" title="{{image.basename}}" alt="{{image.basename}}" class="center-block img-rounded img-responsive" />
            <span class="hidden-xxs">{{image.basename}}</span>
        </td>
    {% endunless %}
    {% endif %}
{% endfor %}
