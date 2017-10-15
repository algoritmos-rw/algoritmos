---
layout: page
title: TPs
permalink: /tps/
---
{% assign hoy = site.time | date: "%Y-%m-%d" %}

TPs
=======

A continuación encontrarán las entregas que iremos planteando a lo largo de la
materia.

{: .table .table-striped}
| TP       | Código      | Fecha de entrega |
|----------|-------------|------------------|{% for tp in site.posts reversed %}{% assign expiracion = tp.fin_cuatrimestre | date: "%Y-%m-%d" %}{% if tp.es_TP and hoy < expiracion %}
|[{{tp.nombre_TP}}]({{tp.link_enunciado | relative_url}}) | [{{tp.zip}}]({{tp.link_zip}}) | {{tp.fecha_entrega}}{% endif %}{% endfor %}
