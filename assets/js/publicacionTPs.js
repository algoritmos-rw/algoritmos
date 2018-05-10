---
---

window.onload = agregarTPsATabla;
function agregarTPsATabla() {
    var dtHoy = new Date();
    var hoy = (dtHoy.getYear() + "/" + dtHoy.getMonth() + 1) + "/" + (dtHoy.getDate());
    {% for x in site.data.trabajos %}{% assign tp = x[1] %}
        var dtPublicacion = new Date("{{tp.publicacion}}");
        var publicacion = (dtPublicacion.getYear() + "/" + dtPublicacion.getMonth() + 1) + "/" + (dtPublicacion.getDate()+1);
        
        var tabla = document.getElementById("tabla-trabajos");
        var fila = document.createElement("tr")
        
        if (hoy >= publicacion) fila.innerHTML += "<td> <a href={{tp.enunciado_link}}'>{{tp.id}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.id}} </td>"
        
        if (hoy >= publicacion) fila.innerHTML += "<td> <a href='{{tp.zip_link}}'>{{tp.zip}}</a> </td>"
        else fila.innerHTML += "<td> {{tp.zip}} </td>"
        
        fila.innerHTML += "<td> {{tp.publicacion}} </td>" 
        fila.innerHTML += "<td> {{tp.entrega}} </td>" 
        tabla.appendChild(fila)
    {% endfor %}

}


