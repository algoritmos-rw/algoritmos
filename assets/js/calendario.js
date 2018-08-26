---
---

window.onload = agregarTPsYParcialitosACalendario;
function agregarTPsYParcialitosACalendario() {
    var tabla = document.getElementById("tabla-calendario");
    var trabajos_y_parcialitos = [];

    {% for t in site.data.trabajos %}{% assign tp = t[1] %}
        var dtEntrega = new Date("{{tp.entrega}}");
        trabajos_y_parcialitos.push([diadelasemana(dtEntrega),dtEntrega,"Entrega de: {{tp.id}}"]);
    {% endfor %}

    {% for p in site.data.parcialitos %}{% assign parcialito = p[1] %}
        var dtEntrega = new Date("{{parcialito.fecha}}");
        trabajos_y_parcialitos.push([diadelasemana(dtEntrega),dtEntrega,"{{parcialito.label}}"]);
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
}

function diadelasemana(fecha){
    var numero = fecha.getDay();
    if (numero == 1) return 'Lunes'
    if (numero == 5) return 'Viernes'
}

function prettyfecha(fecha){
    return fecha.getDate() + '/' + (fecha.getMonth()+1) + '/' + (fecha.getFullYear());
}

function byDate(a,b) {
    return a[1] - b[1];
}
