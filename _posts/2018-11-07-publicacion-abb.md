---
layout: post
title: "Publicado TDA ABB"
date: 2018-11-07 15:00:00 -0300

trabajo: ABB
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.