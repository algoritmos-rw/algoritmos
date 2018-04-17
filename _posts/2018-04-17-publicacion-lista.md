---
layout: post
title: "Publicado TDA Lista"
date: 2018-04-17 00:25:00 -0300

trabajo: 'Lista'
---

{% for tp in site.data.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
