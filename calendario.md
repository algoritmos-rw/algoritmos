Calendario
==========

La materia será dictada en 32 clases a lo largo de 16 semanas.
Cada clase estará dividida en una parte teórica y una práctica, de 1:30 hs cada una.
Las clases teóricas se dictarán los días lunes y viernes de 17:30 a 19:00 hs y las clases prácticas, los mismos días en el horario de 19:00 a 20:30 hs.

Además, contamos con un [calendario detallado]({{site.data.cuatrimestre.calendario_detallado}}) de las clases para descargar.

Fechas de examen:

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
- **1er parcialito**: Punteros. Memoria estática y dinámica. Recursividad. Algoritmos de división y conquista. Cálculo de eficiencia. Teorema Maestro. TDAs. Pilas. Colas. Listas. Iteradores de listas. Ordenamientos comparativos y no comparativos.
- **2do parcialito**: Diccionarios. Hash abierto y cerrado. Árboles binarios. ABB. Iteradores internos y externos de árboles binarios. árboles AVL. Árboles B. Heap y heapsort.
- **3er parcialito**: Grafos: Implementaciones y usos de grafos. Recorridos DFS y BFS y aplicaciones de éstos. Camino mínimo (algoritmos de Dijkstra, BFS y Bellman-Ford). Árboles de tendido mínimo (algoritmos de Prim y Kruskal). Redes de Flujo (algoritmo de Bellman-Ford).

Finales
-------

{: .table .table-striped}
| **Día**       | **Fecha**      | Horario 			| **Detalle** |{%for f in site.data.finales%}{% assign final = f[1] %}
| {{final.dia}} | {{final.fecha}}| 18:00 - 21:00 	| [Notas]({{final.link}}){% endfor %}


 <script src="{{ '/assets/js/calendario.js' | relative_url }}"></script>
