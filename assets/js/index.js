---
---

const FILA_PRIMERA_CLASE = 3;
const LUNES_A_VIERNES = 4;
const VIERNES_A_LUNES = 3; 
const COLUMNA_INICIAL = "D";
const COLUMNA_FINAL = "J";
const CANT_CLASES = 5;
const CANT_CLASES_ANTERIORES = 1;

var desde = new Date();
desde.setDate(new Date().getDate() - 15);
var hasta = new Date();
hasta.setDate(new Date().getDate() + 21);

window.onload = function() {
	let fechas = agregarTPsYParcialitosACalendario(desde, hasta);
	if (fechas.length == 0) {
		let calendario = document.getElementById('calendario');
		calendario.style.display = 'none';
	}
	agregarCalendarioDetallado();
}

function agregarCalendarioDetallado() {
	var calendario = document.getElementById("embedded-calendario");
	var embedded = document.createElement("iframe");
	embedded.setAttribute("src", urlCalendario());
    embedded.setAttribute("width", "100%");
    calendario.appendChild(embedded);
}

function filaInicial() {
	const MILIS_EN_UN_DIA = 24 * 3600 * 1000;
	clase = new Date("{{site.data.cuatrimestre.primera_clase}}");
	actual = new Date();
	
	siguiente_clase_diff = LUNES_A_VIERNES;
	fila = FILA_PRIMERA_CLASE
	while (clase < actual) {
		clase = new Date((clase.getTime() + siguiente_clase_diff * MILIS_EN_UN_DIA));
		if (clase < actual) {
			fila++;
		}
		siguiente_clase_diff = siguiente_clase_diff == LUNES_A_VIERNES ? VIERNES_A_LUNES : LUNES_A_VIERNES; 
	}
	return fila - CANT_CLASES_ANTERIORES;
}

function urlCalendario() {
	var inicial = filaInicial();
	var final = inicial + CANT_CLASES - 1;
	return "{{site.data.cuatrimestre.calendario_detallado}}&range=" + 
		COLUMNA_INICIAL + inicial + ":" + COLUMNA_FINAL + final + 
		"&widget=false&chrome=false&headers=false";
}
