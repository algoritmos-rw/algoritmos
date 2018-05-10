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
    var hoy = (dtHoy.getYear() + "/" + dtHoy.getMonth() + 1) + "/" + (dtHoy.getDate()+1);
    
    var dtFinCuatrimestre = new Date("{{site.data.cuatrimestre.fin_cuatrimestre}}");
    var finCuatrimestre = (dtFinCuatrimestre.getYear() + "/" + dtFinCuatrimestre.getMonth() + 1) + "/" + (dtFinCuatrimestre.getDate()+1);
    
    {% for x in site.data.trabajos %}{% assign tp = x[1] %}
        var dtPublicacion = new Date("{{tp.publicacion}}");
        var dtEntrega = new Date("{{tp.entrega}}");
        var publicacion = dtPublicacion.getYear() + "/" + (dtPublicacion.getMonth() + 1) + "/" + (dtPublicacion.getDate()+1);
        
        var tabla = document.getElementById("tabla-trabajos");
        var fila = document.createElement("tr")
        
        if (hoy >= publicacion && hoy <= finCuatrimestre) fila.innerHTML += "<td> <a href={{tp.enunciado_link}}'>{{tp.id}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.id}} </td>"
        
        if (hoy >= publicacion && hoy <= finCuatrimestre) fila.innerHTML += "<td> <a href='{{tp.zip_link}}'>{{tp.zip}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.zip}} </td>"
        var prettyPublicacion = dtPublicacion.getDate() + ' de ' + monthNames[dtPublicacion.getMonth()];
        var prettyEntrega = dtEntrega.getDate() + ' de ' + monthNames[dtEntrega.getMonth()];

        if (hoy <= finCuatrimestre) fila.innerHTML += "<td>" + prettyPublicacion + "</td>"
        else fila.innerHTML += "<td> </td>"

        if (hoy <= finCuatrimestre) fila.innerHTML += "<td>" + prettyEntrega + "</td>"
        else fila.innerHTML += "<td> </td>"

        tabla.appendChild(fila)
    {% endfor %}

}


