#!/usr/bin/env bash

error() {
	echo "$1" >&2
	exit 1
}

uso() {
error "
Uso: $0 [-v] [-b] programa

Argumentos:
  programa          programa a ejecutar
  -v                correr valgrind
  -b                modo batch (no interactivo)
"
}

# Ruta absoluta de este script:
ROOT=`dirname $0`
ROOT=`readlink -e "$ROOT"`

CORRER_VALGRIND=0

if [ -t 1 ]; then
	INTERACTIVO=1
else
	INTERACTIVO=0
fi
COLUMNAS=80

while [ $# -gt 0 ]; do
	case "$1" in
		"-b")
			INTERACTIVO=0
			;;
		"-v")
			CORRER_VALGRIND=1
			;;
		*)
			[ -z "$PROGRAMA" ] || uso
			PROGRAMA="$1"
			;;
	esac
	shift
done

[ "$PROGRAMA" ] || uso

# Ruta absoluta del programa:
PROGRAMA=`readlink -e "$PROGRAMA"`

if [ $INTERACTIVO == 1 ]; then
	COLOR_RESALTAR="\e[1m"
	COLOR_NORMAL="\e[0m"
	COLOR_ROJO="\e[91m"
	COLOR_VERDE="\e[92m"
	COLOR_CYAN="\e[96m"
	COLUMNAS=`tput cols`
fi

# Somos permisivos con las mayusculas y los espacios:
DIFF_ARGS="-i -w -B --strip-trailing-cr"

# Crear archivos temporales:
MKTEMP="mktemp pruebasXXXXX.tmp"
tmp_entrada_test=`$MKTEMP`
tmp_salida_test=`$MKTEMP`
tmp_salida=`$MKTEMP`
tmp_valgrind=`$MKTEMP`
tmp_stderr=`$MKTEMP`

# Borrar archivos temporales antes de salir:
function atexit_func {
	rm -f "$tmp_salida" "$tmp_entrada_test" "$tmp_salida_test" "$tmp_valgrind" "$tmp_stderr"
}
trap "atexit_func" EXIT

pruebas=("$ROOT"/*.test)
ok=0

for ((i = 0; i < ${#pruebas[@]}; i++))
do
	f="${pruebas[$i]}"
	prueba_actual=`basename "$f" .test`
	
	echo -ne "${COLOR_RESALTAR}${prueba_actual}:${COLOR_NORMAL} "
	
	# Obtener entrada y salida a partir del archivo de descripcion la prueba:
	cat "$f" | grep '^<' | cut -c 1 --complement >"$tmp_entrada_test"
	cat "$f" | grep '^>' | cut -c 1 --complement >"$tmp_salida_test"

	if [ $CORRER_VALGRIND == 1 ]; then
		valgrind --leak-check=full --show-reachable=yes -q --log-file="$tmp_valgrind" "$PROGRAMA" <"$tmp_entrada_test" >"$tmp_salida" 2>"$tmp_stderr"
	else
		"$PROGRAMA" <"$tmp_entrada_test" >"$tmp_salida" 2>"$tmp_stderr"
	fi

	cod_salida="$?"
	
	if [ $CORRER_VALGRIND == 1 -a -s "$tmp_valgrind" ]; then
		valgrind_ok=0
	else
		valgrind_ok=1
	fi
	
	# Comparamos la salida con la esperada:
	salida_ok=0
	diff $DIFF_ARGS -q "$tmp_salida_test" "$tmp_salida" >/dev/null 2>&1 && salida_ok=1

	if [ $cod_salida == 0 -a $salida_ok == 1 -a $valgrind_ok == 1 ]; then
		echo -e "${COLOR_VERDE}OK${COLOR_NORMAL}"
		ok=$(( $ok + 1 ))
		continue
	fi
	
	# Mostramos que la prueba fallo y por que:
	echo -en "${COLOR_ROJO}ERROR${COLOR_NORMAL}"
	if [ $cod_salida != 0 ]; then
		echo -e " (codigo de salida: $cod_salida)"
	elif [ $valgrind_ok != 1 ]; then
		echo -e " (errores en valgrind)"
	else
		echo -e ""
	fi
	
	# Mostramos la entrada:
	echo
	echo -e "${COLOR_CYAN}Entrada:${COLOR_NORMAL}"
	cat "$tmp_entrada_test"
	
	# Mostramos un diff de la salida y la esperada:
	if [ $salida_ok != 1 ]; then
		echo
		echo -en "${COLOR_CYAN}"
		printf "%-"$(($COLUMNAS / 2))"s" "Salida esperada:"
		echo -e "  Salida obtenida:${COLOR_NORMAL}"
		diff $DIFF_ARGS -y -W $COLUMNAS "$tmp_salida_test" "$tmp_salida"
	fi
	
	# Mostramos la salida stderr:
	if [ -s "$tmp_stderr" ]; then
		echo
		echo -e "${COLOR_CYAN}stderr:${COLOR_NORMAL}"
		cat "$tmp_stderr"
	fi

	# Mostramos la salida de valgrind:
	if [ $valgrind_ok != 1 -a -s "$tmp_valgrind" ]; then
		echo
		echo -e "${COLOR_CYAN}valgrind:${COLOR_NORMAL}"
		cat "$tmp_valgrind"
	fi

	echo

	# Preguntamos (una vez sola) si seguimos con el resto de las pruebas:
	if [ $INTERACTIVO == 1 ];then
		if [ -z "$continuar" ]; then
			echo -n "Continuar ejecutando el resto de las pruebas? [s/N] "
			read continuar
			if [ -z "$continuar" ]; then
				continuar="n"
			fi
		fi
		if [ x"$continuar" != xs ]; then
			break
		fi
	fi
done

echo
echo "Pruebas exitosas: $ok / ${#pruebas[@]}"

