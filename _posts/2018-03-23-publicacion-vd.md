---
layout: post
title: "Vector dinámico publicado"
date: 2018-03-23 18:00:00 -0300

trabajo: VD
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
