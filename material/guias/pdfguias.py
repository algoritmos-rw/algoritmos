#!/usr/bin/python3

import os
import subprocess
import shutil

ARCHIVOS = ["tdas_conceptos.md", "dyc.md", "ordenamientos.md", "hash.md", "arboles.md", "heap.md", "grafos.md", "grafos_2.md"]
TEMP_DIR = "pdfguias-temp"

os.mkdir(TEMP_DIR)

for archivo in ARCHIVOS:
    with open(archivo) as f:
        with open(TEMP_DIR + "/" + archivo, "w") as s:
            # Remove title, permalink and math:true + '---'
            for i in range(5):
                f.readline()
            for line in f:
                if "TOC" in line or "toc" in line or "## Contenidos" in line: continue
                line = line.replace("$$", "$")
                line = line.replace("★", "$\\star$")
                line = line.replace("\\lt", "<")
                line = line.replace("{:.lower_alpha}", "")
                line = line.replace("{::options toc_levels=\"2\" /}", "")
                if "<img src=" in line:
                    split_line = line.split("\"")
                    line = "    ![](" + split_line[1] + "){width=" + split_line[5] + "}\n"
                s.write(line)

            s.write("\\newpage\n")

temps = [TEMP_DIR + "/" + archivo for archivo in ARCHIVOS]

comando = ["pandoc", "intro.md"] + temps + ["-o", "guias.pdf"]

subprocess.run(comando)

shutil.rmtree(TEMP_DIR)
