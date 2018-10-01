---
layout: post
title: "Publicado Enunciado TP1"
date: 2018-10-01 10:00:00 -0300

trabajo: TP1
---

{% assign TP = site.data.trabajos[page.trabajo] %}
Publicado: [{{TP.id}}]({{TP.enunciado_link | relative_url }}) para el {{TP.entrega | date: "%d/%m" }}.
