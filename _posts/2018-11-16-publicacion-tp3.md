---
layout: post
title: "Publicado Enunciado TP3"
date: 2018-11-16 19:00:00 -0300

trabajo: TP3
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
