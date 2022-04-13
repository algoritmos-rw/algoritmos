package fraccion

type Fraccion struct {
	// ?
}

// CrearFraccion crea una fraccion con el numerador y denominador indicados. 
// Si el denominador es 0, entra en panico.
func CrearFraccion(numerador, denominador int) Fraccion {
	// ??
}

// Sumar crea una nueva fraccion, con el resultante de hacer la suma de las fracciones originales
func (f Fraccion) Sumar(otra Fraccion) Fraccion {
	// ??
}

// Multiplicar crea una nueva fraccion con el resultante de multiplicar ambas fracciones originales
func (f Fraccion) Multiplicar(otra Fraccion) Fraccion {
	// ??
}

// ParteEntera devuelve la parte entera del numero representado por la fracción. 
// Por ejemplo, para "7/2" = 3.5 debe devolver 3. 
func (f Fraccion) ParteEntera() int {
	// ??
}


// Representacion devuelve una representación en cadena de la fraccion simplificada (por ejemplo, no puede devolverse
// "10/8" sino que debe ser "5/4"). Considerar que si se trata de un número entero, debe mostrarse como tal.
// Considerar tambien el caso que se trate de un número negativo. 
func (f Fraccion) Representacion() string {
	// ?
}

