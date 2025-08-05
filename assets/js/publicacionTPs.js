---
---

var monthNames = [
    "Enero", "Febrero", "Marzo",
    "Abril", "Mayo", "Junio", "Julio",
    "Agosto", "Septiembre", "Octubre",
    "Noviembre", "Diciembre"
  ];

function prettyDate(dt) {
    return dt.getUTCDate() + ' de ' + monthNames[dt.getUTCMonth()];
}

window.onload = agregarTPsATabla;
function agregarTPsATabla() {
    var dtHoy = new Date();    
    var dtFinCuatrimestre = new Date("{{site.data.cuatrimestre.fin_cuatrimestre}}");
    
    {% for x in site.data.trabajos %}{% assign tp = x[1] %}
        var dtPublicacion = new Date("{{tp.publicacion}}");
        var dtEntrega = new Date("{{tp.entrega}}");
        
        var dts = [dtPublicacion, dtEntrega]
        var prettyDts = dts.map(prettyDate)

        var tabla = document.getElementById("tabla-trabajos");
        var fila = document.createElement("tr")
        
        if (dtHoy >= dtPublicacion && dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td> <a href='{{tp.enunciado_link | relative_url}}'>{{tp.id}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.id}} </td>"
    
        prettyDts.forEach(function(prettyDt) {
            if (dtHoy <= dtFinCuatrimestre) fila.innerHTML += "<td>" + prettyDt + "</td>"
            else fila.innerHTML += "<td> </td>"
        })

        tabla.appendChild(fila)
    {% endfor %}
}


