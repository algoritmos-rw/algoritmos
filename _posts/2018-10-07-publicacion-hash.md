---
layout: post
title: "Publicado TDA Hash"
date: 2018-10-07 10:00:00 -0300

trabajo: Hash
---
{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m"}}.
