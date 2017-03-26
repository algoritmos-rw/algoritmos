#!/usr/bin/env bash

set -eu

export TIME="Tardó: %Us - Consumió: %M KiB"
PROGRAMA="$1"
RET=0

# Correr con diff y sin Valgrind.
for x in *_in; do
    b=${x%_in}
    $PROGRAMA <${b}_in ${b}_doctores ${b}_pacientes | diff -u ${b}_out - || RET=$?
done

# Salir si hubo errores de diff.
if [[ $RET -ne 0 ]]; then
    exit $RET
fi

# Correr con Valgrind y sin diff.
for x in *_in; do
    b=${x%_in}
    command time valgrind --leak-check=full --track-origins=yes --error-exitcode=2 \
        $PROGRAMA <${b}_in ${b}_doctores ${b}_pacientes >/dev/null || RET=$?
done

exit $RET
