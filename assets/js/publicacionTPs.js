---
---

var monthNames = [
    "Enero", "Febrero", "Marzo",
    "Abril", "Mayo", "Junio", "Julio",
    "Agosto", "Septiembre", "Octubre",
    "Noviembre", "Diciembre"
  ];


window.onload = agregarTPsATabla;
function agregarTPsATabla() {
    var dtHoy = new Date();    
    var dtFinCuatrimestre = new Date("{{site.data.cuatrimestre.fin_cuatrimestre}}");
    
    {% for x in site.data.trabajos %}{% assign tp = x[1] %}
        var dtPublicacion = new Date("{{tp.publicacion}}");
        var dtEntrega = new Date("{{tp.entrega}}");
        
        var tabla = document.getElementById("tabla-trabajos");
        var fila = document.createElement("tr")
        
        if (dtHoy >= dtPublicacion && dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td> <a href='{{tp.enunciado_link | relative_url}}'>{{tp.id}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.id}} </td>"
        
        var prettyPublicacion = dtPublicacion.getUTCDate() + ' de ' + monthNames[dtPublicacion.getUTCMonth()];
        var prettyEntrega = dtEntrega.getUTCDate() + ' de ' + monthNames[dtEntrega.getUTCMonth()];

        if (dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td>" + prettyPublicacion + "</td>"
        else fila.innerHTML += "<td> </td>"

        if (dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td>" + prettyEntrega + "</td>"
        else fila.innerHTML += "<td> </td>"

        tabla.appendChild(fila)
    {% endfor %}

}


