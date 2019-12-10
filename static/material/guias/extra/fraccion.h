#ifndef __FRAC_H_
#define __FRAC_H_

typedef struct fraccion fraccion_t;

/**
Crea una fraccion con el numerador y denominador indicados. 
Si el denominador es 0, o hubo algún error, devuelve NULL.
**/
fraccion_t* fraccion_crear(int numerador, int denominador);

/**
- Crea una nueva fraccion, con el resultante de hacer la suma de las fracciones originales
- Las fracciones originales son destruidas
En caso de algún error, la función devuelve NULL y las fracciones originales no serán destruidas
**/
fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2);

/**
- Crea una nueva fraccion, con el resultante de multiplicar ambas fracciones originales
- Las fracciones originales son destruidas
En caso de algún error, la función devuelve NULL y las fracciones originales no serán destruidas
**/
fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2);

/**
Devuelve la parte entera del numero representado por la fracción. Por ejemplo, para "7/2" = 3.5 debe
devolver 3. 
**/
int fraccion_parte_entera(fraccion_t* fraccion);

/**
Devuelve una representación en cadena de la fraccion simplificada (por ejemplo, no puede devolverse
"10/8" sino que debe ser "5/4"). Considerar que si se trata de un número entero, debe mostrarse como tal.
Considerar tambien el caso que se trate de un número negativo. 
La cadena devuelta provendrá de memoria dinámica por lo que el usuario debe liberarla usando free. 
**/
char* fraccion_representacion(fraccion_t* fraccion);

/**
Destruye una fracción, liberando toda la memoria asociada. 
**/
void fraccion_destruir(fraccion_t* fraccion);

#endif
