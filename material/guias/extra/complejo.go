package complejo

type Complejo struct {
	// ?
}

// CrearComplejo devuelve un puntero a la estructura que representa el numero complejo
// dado por la parte real e imaginaria pasadas por parámetro. 
func CrearComplejo(real float, img float) Complejo {
	// ?
}


// Multiplicar dados dos números complejos, modifica el primero (c1) dejando el resultado de hacer
// la multiplicacion entre ambos números. Recordar que: 
// c1 * c2 = (a + i b) * (c + i d) = (a * c - b * d) + i (b * c + a * d)
func (comp *Complejo) Multiplicar(otro Complejo) {
	// ?
}


// Dados dos números complejos, modifica el primero (c1) dejando el resultado de hacer
// la suma entre ambos números. Recordar que: 
// c1 + c2 = (a + i b) + (c + i d) = (a + c) + i (b + d)
func (comp *Complejo) Sumar(otro Complejo) {

}


// ParteReal Obtiene la parte real de un numero complejo
func (comp Complejo) ParteReal() float {
	// ?
}

// ParteImaginaria Obtiene la parte imaginaria de un numero complejo
func (comp Complejo) ParteImaginaria() float {
	// ?
}

// Modulo Obtiene el modulo de un numero complejo
func (comp Complejo) Modulo() float {
	// ?
}

// Angulo Obtiene el angulo de un numero complejo
func (comp Complejo) Angulo() float {
	// ?
}
