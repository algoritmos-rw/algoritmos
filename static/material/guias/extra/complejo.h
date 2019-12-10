#ifndef __COMPLEJO_H__
#define __COMPLEJO_H__

typedef struct complejo complejo_t;


/**
Devuelve un puntero a la estructura que representa el numero complejo
dado por la parte real e imaginaria pasadas por parámetro. 
**/
complejo_t* complejo_crear(double real, double img);

/**
Destruye la estructura liberando la memoria asociada. 
**/
void complejo_destruir(complejo_t* complejo);

/**
Dados dos números complejos, modifica el primero (c1) dejando el resultado de hacer
la multiplicacion entre ambos números. Recordar que: 
c1 * c2 = (a + i b) * (c + i d) = (a * c - b * d) + i (b * c + a * d)
**/
void complejo_multuplicar(complejo_t* c1, complejo_t* c2);

/**
Dados dos números complejos, modifica el primero (c1) dejando el resultado de hacer
la suma entre ambos números. Recordar que: 
c1 + c2 = (a + i b) + (c + i d) = (a + c) + i (b + d)
**/
void complejo_sumar(complejo_t* c1, complejo_t* c2);

/**
Obtiene la parte real de un numero complejo
**/
double complejo_obtener_real(const complejo_t* complejo);

/**
Obtiene la parte imaginaria de un numero complejo
**/
double complejo_obtener_imaginaria(const complejo_t* complejo);

/**
Obtiene el modulo de un numero complejo
**/
double complejo_obtener_modulo(const complejo_t* complejo);

/**
Obtiene el ángulo del número complejo con el eje real (para la representacion trigonometrica)
**/
double complejo_obtener_angulo(const complejo_t* complejo);


#endif