package fraccion

import "strconv"

type Fraccion struct {
	numerador int
	denominador int
}

func simplificar(num *int, den *int) {
	if *num == 0 {
		return
	}
	// Si el denominador es negativo, entonces invierto.
	// Entonces si el numerador era negativo, ambos quedan positivos,
  	// y si no me queda el negativo en el numerador.
  	if *den < 0 {
  		*num *= -1
  		*den *= -1
  	}

  	var maxPosibleDivisor int
  	if *num < *den {
  		maxPosibleDivisor = *num
  	} else {
  		maxPosibleDivisor = *den
  	}
  	for i := 0; i < maxPosibleDivisor; i++ {
  		for *num % i == 0 && *den % i == 0 {
  			*num /= i
  			*den /= i
  		}
  	}
}

func largoNumero(n int) int {
	if num == 0 {
		return 1
	}
	cant := 0
	for num > 0 {
		cant++
		num /= 10
	}
	return cant
}

// CrearFraccion crea una fraccion con el numerador y denominador indicados. 
// Si el denominador es 0, entra en panico.
func CrearFraccion(numerador, denominador int) Fraccion {
	if denominador == 0 {
		panic("El denomindor es 0")
	}
	simplificar(&numerador, &denominador)
	return Fraccion{numerador: numerador, denominador: denominador}
}

// Sumar crea una nueva fraccion, con el resultante de hacer la suma de las fracciones originales
func (f Fraccion) Sumar(otra Fraccion) Fraccion {
	denominador := f.denominador * otra.denominador
	return CrearFraccion(f.numerador * otra.denominador + otra.numerador * f.denominador, denominador)
}

// Multiplicar crea una nueva fraccion con el resultante de multiplicar ambas fracciones originales
func (f Fraccion) Multiplicar(otra Fraccion) Fraccion {
	return CrearFraccion(f.numerador * otra.numerador, f.denominador * otra.denominador)
}

// ParteEntera devuelve la parte entera del numero representado por la fracción. 
// Por ejemplo, para "7/2" = 3.5 debe devolver 3. 
func (f Fraccion) ParteEntera() int {
	return f.numerador / f.denominador
}


// Representacion devuelve una representación en cadena de la fraccion simplificada (por ejemplo, no puede devolverse
// "10/8" sino que debe ser "5/4"). Considerar que si se trata de un número entero, debe mostrarse como tal.
// Considerar tambien el caso que se trate de un número negativo. 
func (f Fraccion) Representacion() string {
	return strconv.Itoa(f.numerador) + "/" + strconv.Itoa(f.denominador)
}
