#! /bin/sh

export TIME="Tardó: %Us - Consumió: %M KiB"

for i in 12500 25000 50000 100000 200000 400000; do
    echo -n "$i elementos - "
    (command time $1 $i)
done
