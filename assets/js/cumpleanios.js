---
---
window.onload = mostrarCumpleanios;
function mostrarCumpleanios() {
    var dtHoy = new Date();
    var hoy = (dtHoy.getMonth() + 1) + "/" + (dtHoy.getDate());

    {% for x in site.data.docentes.ayudantes %}
        var dtCumple = new Date("1900-" + "{{x.cumple}}");
        var cumple = (dtCumple.getMonth() + 1) + "/" + (dtCumple.getDate()+1);
        if (cumple == hoy){
            document.getElementById("cumpleanios").innerHTML = "¡Hoy cumple {{x.apodo}}!";
        }
    {% endfor %}

    document.getElementById("cumpleanios").style.display = "block";
}