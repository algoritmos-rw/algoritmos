---
layout: post
title: "Publicado TDA Lista"
date: 2018-04-17 00:25:00 -0300

trabajo: Lista
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
