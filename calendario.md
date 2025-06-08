Calendario
==========

La materia será dictada en 32 clases a lo largo de 16 semanas.

Cada clase estará dividida en una parte teórica y una práctica, de 1:30 hs cada una.

Las clases teóricas se dictarán los días lunes y jueves de 17:30 a 19:00 hs y las clases prácticas, los mismos días en el horario de 19:00 a 20:30 hs.

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
- **1er parcialito**: Punteros. Recursividad. Algoritmos de división y conquista. Cálculo de eficiencia. Teorema Maestro. TDAs. Pilas. Colas y Listas. Ordenamientos comparativos y no comparativos.
- **2do parcialito**: Diccionarios. Hash abierto y cerrado. Árboles binarios. ABB. Iteradores internos y externos de árboles binarios. árboles AVL.  Heap y Heapsort.
- **3er parcialito**: Grafos.

Finales
-------

{: .table .table-striped}
| **Día**       | **Fecha**      | Horario 			| **Detalle** |{%for f in site.data.finales%}{% assign final = f[1] %}
| {{final.dia}} | {{final.fecha}}| {{final.horario}} {% endfor %}

[Planilla de notas de final]({{site.data.finales.planilla}}).


 <script src="{{ '/assets/js/calendario.js' | relative_url }}"></script>
