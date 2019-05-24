---
---


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

