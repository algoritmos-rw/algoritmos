---
layout: post
title: "Publicado Enunciado TP2"
date: 2018-10-29 19:00:00 -0300

trabajo: TP2
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
