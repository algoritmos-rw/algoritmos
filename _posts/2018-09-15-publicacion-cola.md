---
layout: post
title: "Publicado TDA Cola"
date: 2018-09-14 19:30:00 -0300

trabajo: Cola
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
