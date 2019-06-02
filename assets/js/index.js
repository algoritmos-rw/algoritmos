---
---

const FILA_PRIMERA_CLASE = 3;
const LUNES_A_VIERNES = 4;
const VIERNES_A_LUNES = 3; 
const COLUMNA_INICIAL = "D";
const COLUMNA_FINAL = "J";
const CANT_CLASES = 5;
const CANT_CLASES_ANTERIORES = 0;

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
}

