---
layout: post
title: "TP0 publicado"
date: 2018-03-17 17:32:00 -0300

trabajo: 'TP0'
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
