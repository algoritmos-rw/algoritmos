---
layout: post
title: "Publicado Enunciado TP3"
date: 2018-06-08 20:00:00 -0300

trabajo: TP3
---

{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega}}.
