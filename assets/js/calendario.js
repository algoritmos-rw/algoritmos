---
---

window.onload = agregarTPsYParcialitosACalendario;
function agregarTPsYParcialitosACalendario(desde, hasta) {
    var tabla = document.getElementById("tabla-calendario");
    var trabajos_y_parcialitos = [];

/*    {% for t in site.data.trabajos %}{% assign tp = t[1] %}
        var dtEntrega = new Date("{{tp.entrega}}");
        var dtPublicacion = new Date("{{tp.publicacion}}");
        if (!desde || !hasta || (dtEntrega >= desde && dtEntrega <= hasta)) {
            var label = "{{tp.id}}";
            if (dtPublicacion <= new Date()) {
                label = "<a href='{{tp.enunciado_link | relative_url}}'>" + label + "</a>";
            }
            trabajos_y_parcialitos.push([diadelasemana(dtEntrega),dtEntrega,"Entrega de: " + label]);
        }
    {% endfor %} */

    {% for p in site.data.parcialitos %}{% assign parcialito = p[1] %}
        var dtEntrega = new Date("{{parcialito.fecha}}");
        if (!desde || !hasta || (dtEntrega >= desde && dtEntrega <= hasta)) {
            trabajos_y_parcialitos.push([diadelasemana(dtEntrega),dtEntrega,"{{parcialito.label}}"]);
        }
    {% endfor %}

    trabajos_y_parcialitos.sort(byDate);

    trabajos_y_parcialitos.forEach(
        function(item){
            var fila = document.createElement("tr");
            fila.innerHTML += "<td>" + item[0] + "</td>";
            fila.innerHTML += "<td>" + prettyfecha(item[1]) + "</td>";
            fila.innerHTML += "<td>" + item[2] + "</td>";
            tabla.appendChild(fila);
        }
    );

    return trabajos_y_parcialitos;
}

function diadelasemana(fecha){
    var numero = fecha.getDay();
    if (numero == 0) return 'Lunes'
    if (numero == 4) return 'Viernes'
}

function prettyfecha(fecha){
    return fecha.getUTCDate() + '/' + (fecha.getUTCMonth()+1) + '/' + (fecha.getFullYear());
}

function byDate(a,b) {
    return a[1] - b[1];
}
