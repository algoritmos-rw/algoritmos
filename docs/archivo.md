---
layout: page
title: Archivo de trabajos prácticos
permalink: /:path/:basename/
---

{% assign cursadas = site.tps | sort: 'deadline' | group_by: 'cursada' | reverse %}

{% for c in cursadas %}

## {{ c.name }}

{% for tp in c.items %}
  - [{{ tp.title }}]({{ tp.url | relative_url }})
{% endfor %}

{% endfor %}
