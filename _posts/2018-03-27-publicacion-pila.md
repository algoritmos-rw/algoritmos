---
layout: post
title: "Pila publicado"
date: 2018-03-27 13:00:00 -0300

trabajo: 'Pila'
---

{% for tp in site.data.trabajos %}
{% if tp.id == page.trabajo %}{% assign TP = tp%}{% endif %}
{% endfor %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.

