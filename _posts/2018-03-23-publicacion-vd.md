---
layout: post
title: "Vector dinámico publicado"
date: 2018-03-23 18:00:00 -0300

trabajo: 'VD'
---

{% for tp in site.data.trabajos.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.