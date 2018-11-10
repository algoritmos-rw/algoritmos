import random

INDICE_CIUDAD = 2
INDICE_AEROPUERTO = 0
INDICE_LAT = 5
INDICE_LONG = 6
INDICE_ORG = 7
INDICE_DST = 8
INDICE_TIEMPO = 15

vuelos = {}

def precio(tiempo):
    return random.randint(round(tiempo * 2.5), round(tiempo * 5))

with open("airports.csv") as f:
    f.readline()
    with open("aeropuertos.csv", "w") as s:
        for line in f:
            campos = line.strip().split(",")
            ciudad, aeropuerto, lat, lng = campos[INDICE_CIUDAD], campos[INDICE_AEROPUERTO], \
                                           campos[INDICE_LAT], campos[INDICE_LONG]
            vuelos[aeropuerto] = {}
            s.write(ciudad + "," + aeropuerto + "," + lat + "," + lng + "\n")

with open("flights.csv") as f:
    f.readline()
    for line in f:
        campos = line.strip().split(",")
        origen, destino, tiempo = campos[INDICE_ORG], campos[INDICE_DST], campos[INDICE_TIEMPO]
        if tiempo == "": continue
        tiempo = int(tiempo)
        if origen not in vuelos or destino not in vuelos:
            continue
        if destino in vuelos[origen]:
            vuelos[origen][destino].append(tiempo)
        elif origen in vuelos[destino]:
            vuelos[destino][origen].append(tiempo)
        else:
            vuelos[origen][destino] = [tiempo]

with open("vuelos.csv", "w") as s:
    for v in vuelos:
        for w in vuelos[v]:
            tiempo_prom = round(sum(vuelos[v][w]) / len(vuelos[v][w]))
            linea = v + "," + w + "," + str(tiempo_prom) + "," + \
                    str(precio(tiempo_prom)) + "," + str(len(vuelos[v][w]))
            s.write(linea + "\n")

