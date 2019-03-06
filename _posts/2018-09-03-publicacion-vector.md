---
layout: post
title: "Vector dinámico publicado"
date: 2018-09-03 19:30:00 -0300

trabajo: Vector
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
