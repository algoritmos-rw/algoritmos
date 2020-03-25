import numpy as np
import random

EXP = 20
SAMPLES = 100


s = np.random.power(EXP, SAMPLES) * SAMPLES
cant_aristas = [int(SAMPLES - i) + 1 for i in s]


with open("minimo.tsv", "w") as f:
	for v in range(SAMPLES):
		ya_vistos = set()
		for i in range(cant_aristas[v]):
			conectar_con = random.randint(0, SAMPLES - 1)
			while conectar_con in ya_vistos:
				conectar_con = random.randInt(0, SAMPLES - 1)
			f.write(str(v) + "\t" + str(conectar_con) + "\n")
