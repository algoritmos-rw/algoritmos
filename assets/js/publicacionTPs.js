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
        
        if (dtHoy >= dtPublicacion && dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td> <a href={{tp.enunciado_link}}'>{{tp.id}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.id}} </td>"
        
        if (dtHoy >= dtPublicacion && dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td> <a href='{{tp.zip_link}}'>{{tp.zip}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.zip}} </td>"
        var prettyPublicacion = dtPublicacion.getDate()+1 + ' de ' + monthNames[dtPublicacion.getMonth()];
        var prettyEntrega = dtEntrega.getDate()+1 + ' de ' + monthNames[dtEntrega.getMonth()];

        if (dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td>" + prettyPublicacion + "</td>"
        else fila.innerHTML += "<td> </td>"

        if (dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td>" + prettyEntrega + "</td>"
        else fila.innerHTML += "<td> </td>"

        tabla.appendChild(fila)
    {% endfor %}

}


