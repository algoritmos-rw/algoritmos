---
layout: post
title: "Publicado TDA Heap"
date: 2018-05-21 10:00:00 -0300

trabajo: Heap
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
