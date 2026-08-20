Calendario
==========

La materia será dictada en 32 clases a lo largo de 16 semanas.

Las clases teóricas se dictarán los días miércoles de 17 a 20 hs y las clases prácticas los días jueves de 18 a 21 hs.

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

Los temas a ser evaluados en cada parcial son:
- **1er parcial**: Punteros. Recursividad. Algoritmos de división y conquista. Cálculo de eficiencia. Teorema Maestro. TDAs. Pilas. Colas y Listas. Ordenamientos comparativos y no comparativos. Diccionarios. Hash abierto y cerrado. 
- **2do parcial**: Árboles binarios. ABB. Iteradores internos y externos de árboles binarios. árboles AVL.  Heap y Heapsort. Grafos.

Finales
-------

{: .table .table-striped}
| **Día**       | **Fecha**      | Horario 			| **Detalle** |{%for f in site.data.finales%}{% assign final = f[1] %}
| {{final.dia}} | {{final.fecha}}| {{final.horario}} {% endfor %}

[Planilla de notas de final]({{site.data.finales.planilla}}).


 <script src="{{ '/assets/js/calendario.js' | relative_url }}"></script>
