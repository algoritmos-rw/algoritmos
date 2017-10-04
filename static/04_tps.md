---
layout: page
title: TPs
permalink: /tps/
---

TPs
=======

A continuación encontrarán los trabajos prácticos para entregar que iremos planteando a lo largo de la materia.

{: .table .table-striped}
| TP       | Código      | Fecha de entrega |
|----------|-------------|------------------|{% for tp in site.data.tps %}{% if tp.is_publicado %}
|[{{tp.nombre}}]({{tp.link_enunciado | relative_url}}) | [{{tp.zip}}]({{tp.link_zip}}) | {{tp.fecha_entrega}}{% endif %}{% endfor %}
