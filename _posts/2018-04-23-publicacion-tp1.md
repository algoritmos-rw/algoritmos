---
layout: post
title: "Publicado Enunciado TP1"
date: 2018-04-23 15:00:00 -0300

trabajo: 'TP1'
---

{% for tp in site.data.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
