"""
Implementacion de problema subset_sum con backtracking. 

Nota: Como se puede ver cada vez que se llama recursivamente a sum_set se realiza un slice de L. Esta operacion puede ser muy costosa, 
para evitar realizarla reiteradas veces, se debe pasar un parametro extra que indique la posicion actual en el arreglo. Tambien se podria 
modificar la implementacion para evitar repetir las sumas de la solucion parcial.
"""


def subset_sum(L, n, solucion_parcial, soluciones):
	# Si encuentro una solucion la agrego a las soluciones
	if sum(solucion_parcial) == n:
		soluciones.append(solucion_parcial[:])
		return
	
	# Si por esta rama me paso, dejo de probar
	if sum(solucion_parcial) > n:
		return
	
	# Si no me paso exploro esa rama
	for i in range(len(L)):
		solucion_parcial.append(L[i])
		subset_sum(L[i+1:], n, solucion_parcial, soluciones)
		solucion_parcial.pop()
	return

