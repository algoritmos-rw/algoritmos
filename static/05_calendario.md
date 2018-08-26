---
layout: page
title: Calendario
permalink: /calendario/
---

Calendario
=========

La materia será dictada en 32 clases a lo largo de 16 semanas.
Cada clase estará dividida en una parte teórica y una práctica, de 1:30 hs cada una.
Las clases teóricas se dictarán los días lunes y viernes de 17:30 a 19:00 hs y las clases prácticas, los mismos días en el horario de 19:00 a 20:30 hs.

Las fechas importantes pueden ser seguidas con [el calendario](https://calendar.google.com/calendar?cid=dHBzLjc1NDFyd0BnbWFpbC5jb20) de la lista de correos.

Contamos con un [calendario detallado]({{site.data.cuatrimestre.calendario_detallado}}) de las clases para descargar.

Fechas importantes:

<table class="table table-striped">
  <tbody id="tabla-calendario">
    <tr>
      <td><strong>Día</strong></td>
      <td><strong>Fecha</strong></td>
      <td><strong>Detalle</strong></td>
    </tr>
  </tbody>
</table>

Los temas a ser evaluados en cada parcialito son:
- **1er parcialito**: Punteros. Memoria estática y dinámica. Recursividad. Algoritmos de división y conquista. Cálculo de eficiencia. Teorema Maestro. TDAs. Pilas. Colas. Listas. **Iteradores de listas.**
- **2do parcialito**: Ordenamientos no comparativos. Diccionarios. Hash abierto y cerrado. Árboles binarios. ABB. Iteradores internos y externos de árboles binarios. AVL. **Árboles B.**
- **3er parcialito**: Heap y heapsort. Grafos: Implementaciones y usos de grafos. Orden topológico. Recorridos DFS y BFS.
- **4to parcialito**: Camino mínimo (algoritmos de Dijkstra y BFS). Árboles de tendido mínimo (algoritmos de Prim y Kruskal). Algoritmos Greedy. Backtracking. Programación dinámica.

(En negrita los temas que no se evaluarán en la primera oportunidad pero sí en recuperatorios.)

Finales
-------

{: .table .table-striped}
| **Día**       | **Fecha**      | **Detalle** |{%for f in site.data.finales%}{% assign final = f[1] %}
| {{final.dia}} | {{final.fecha}}| {{final.detalle}}{% endfor %}


 <script src="{{ '/assets/js/calendario.js' | relative_url }}"></script>
