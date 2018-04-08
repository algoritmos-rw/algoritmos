---
layout: post
title: "Publicado TDA Cola"
date: 2018-04-07 15:00:00 -0300

trabajo: 'Cola'
---

{% for tp in site.data.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
