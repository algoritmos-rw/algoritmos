---
layout: post
title: "TP0 publicado"
date: 2018-03-17 17:32:00 -0300

trabajo: 'TP0'
---

{% for tp in site.data.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.