---
layout: post
title: "Pila publicado"
date: 2018-03-27 13:00:00 -0300

trabajo: Pila
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
