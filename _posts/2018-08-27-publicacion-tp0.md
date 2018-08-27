---
layout: post
title: "TP0 publicado"
date: 2018-08-27 19:30:00 -0300

trabajo: TP0
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
