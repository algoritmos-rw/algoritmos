---
math: true
---

# Árboles Binarios, ABB, AVL, Árbol B
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Se tiene un árbol binario de búsqueda con cadenas como claves y
función de comparación `strcmp`. Implementar una primitiva
`func (abb *abb[K, V]) Mayores(cadena K) Lista[K]`
que, dados un ABB y una clave, devuelva una
lista ordenada con las claves del árbol estrictamente mayores a la
recibida por parámetro (que no necesariamente está en el árbol). Implementar sin utilizar el iterador Interno del ABB. 

Suponer que la estructura del TDA es:

```golang
type abb struct {
    clave string
    izq *abb
    der *abb
}
```

_Aclaración_: se debe realizar la menor cantidad posible de comparaciones.

### Solución

La aclaración hace mención a que utilicemos la propiedad de ABB: sabemos que los nodos
a izquierda son menores al actual, y los que estén a derecha son mayores.
En particular, si estamos en un nodo cuya clave es menor (o igual) a la buscada, entonces es innecesario
revisar a izquierda: todos esos nodos también serán menores. Sí tendremos siempre que revisar a derecha,
porque no es posible descartar. Esto es similar a una búsqueda por rango, solo que sin un límite superior.

```cpp
lista_t* abb_mayores(const abb_t* abb, const char* clave) {
    lista_t* mayores = lista_crear();
    if (!mayores) {
        return NULL;
    }
    _abb_mayores(abb, clave, mayores);
    return claves;
}

void _abb_mayores(const abb_t* abb, const char* clave, lista_t* claves) {
    // caso base SIEMPRE
    if (abb == NULL) {
        return;
    }
    // si la actual es mayor, llamamos a la izquierda y guardamos la actual
    if (strcmp(abb->clave, clave) > 0) {
        _abb_mayores(abb->izq, clave, claves);
        lista_insertar_primero(claves, abb->clave);
    }
    _abb_mayores(abb->der, clave, claves);
}
```

Ya que estamos, vemos la complejidad: En el peor de los casos, se pasa una clave que es menor a la mínima, por lo que se
ven todos los nodos, así que será $$\mathcal{O}(n)$$. Por si nos interesara el mejor caso, esto sería con una clave mayor
o igual a la máxima clave del árbol, por lo que recorreríamos la rama derecha, haciéndose en $$\Omega(\log n)$$ (recordar, la notación $$\Omega$$ es una cota inferior, a diferencia de $$\mathcal{O}$$ que es una cota superior).


## Ejercicios propuestos

1.  (★) Dado un árbol binario, escribir una primitiva recursiva que determine la altura del mismo. Indicar
    y justificar el orden de la primitiva.

1.  (★) Implementar una primitiva que devuelva la suma de todos los datos (números) de un árbol binario.
    Indicar y justificar el orden de la primitiva.

1.  (★) Se tiene un AB con números enteros como datos, y se quiere reemplazar cada dato por el resultado de multiplicarlo con los datos de los hijos.
    Hacer un seguimiento de hacer dicho procesamiento con un preorder, inorder o postorder. A continuación se deja
    la implementación mediante cada recorrido:

    ```golang
    func datoONeutro(ab *arbol[int]) int {
        if ab == nil {
            return 1
        } else {
            return ab.dato
        }
    }
    
    func MultiplicarConHijosPre(arbol *Arbol[int]) {
        if arbol == nil {
            return  
        } 
        valor_izq := datoONeutro(arbol.izq)
        valor_der := datoONeutro(arbol.der)
        arbol.dato *= valor_izq * valor_der
        MultiplicarConHijosPre(arbol.izq)
        MultiplicarConHijosPre(arbol.der)
    }

    func MultiplicarConHijosIn(arbol *Arbol[int]) {
        if arbol == nil {
            return  
        } 
        MultiplicarConHijosIn(arbol.izq)
        valor_izq := datoONeutro(arbol.izq)
        valor_der := datoONeutro(arbol.der)
        arbol.dato *= valor_izq * valor_der
        MultiplicarConHijosIn(arbol.der)
    }

    func MultiplicarConHijosPos(arbol *Arbol[int]) {
        if arbol == nil {
            return
        } 
        MultiplicarConHijosPos(arbol.izq)
        MultiplicarConHijosPos(arbol.der)
        valor_izq := datoONeutro(arbol.izq)
        valor_der := datoONeutro(arbol.der)
        arbol.dato *= valor_izq * valor_der
    }
    ```

1.  (★★) Dado un árbol binario, escriba una _primitiva_ recursiva que cuente la cantidad de nodos que
    tienen exactamente dos hijos directos. ¿Qué orden de complejidad tiene la función implementada?

1.  (★★) Escribir una _primitiva_ con la firma `func (arbol *Arbol) Invertir()`
    que invierta el árbol binario pasado por parámetro, de manera tal que los hijos
    izquierdos de cada nodo se conviertan en hijos derechos.

    La estructura `Arbol` respeta la siguiente definición:

    ```golang
        type Arbol struct {
            izq *Arbol
            der *Arbol
        }
    ```

    Indicar el orden de complejidad de la función implementada.

1.  (★★) Suponer que se tiene un ABB _A_ con una función de comparación `cmp1` con $$n$$ claves. También, se
    tiene otro ABB vacío _B_ con función de comparación `cmp2` (con `cmp1` y `cmp2` diferentes).
    ¿Es posible insertar en algún orden todas las claves de _A_ en _B_ de tal forma que ambos tengan
    exactamente la misma estructura? Si es posible, describir un algoritmo que permita lograr esto; si no lo es, razonar por qué. (Considerar que la lógica a emplear debe funcionar para cualquier valor de $$n$$ y cualquier estructura
    que tenga el ABB _A_.)

1.  (★★★) Se tiene un AVL con números enteros como claves (su función de comparación simplemente compara
    dichos valores de la forma tradicional). Su estado inicial puede reconstruirse a partir del
    preorder: `15 - 6 - 4 - 7 - 50 - 23`. Hacer el seguimiento de las siguientes inserciones,
    incluyendo rotaciones intermedias: `71 - 27 - 38 - 19 - 11 - 21 - 24 - 25`.

1.  (★★★) Mostrar cómo se modifica la estructura de un árbol B (incluyendo los pasos intermedios) con tamaño
    para 3 claves por nodo que inicialmente se encuentra vacío, al aplicar las siguientes operaciones:
    insertar 14, insertar 2, insertar 10, insertar 6, insertar 7, insertar 1, insertar 4, insertar 8,
    insertar 11, insertar 19, insertar 9, insertar 5, insertar 15, insertar 3.

1.  (★★★) Definimos como _quiebre en un árbol binario_ cuando ocurre que:
    - un hijo derecho tiene un solo hijo, y es el izquierdo
    - un hijo izquierdo tiene un solo hijo, y es el derecho

    Implementar una _primitiva_ para el árbol binario `func (arbol Arbol) Quiebres() int`
    que, dado un árbol binario, nos devuelva la cantidad de quiebres que
    tiene. La primitiva no debe modificar el árbol. La estructura del
    tipo `Arbol` es:

    ```golang
        type Arbol struct {
            izq *Arbol
            der *Arbol
        }
    ```

    Indicar y justificar el orden de la primitiva, e indicar el tipo de
    recorrido implementado.

1.  (★★) Indicar si las siguientes afirmaciones son verdaderas o falsas. En caso de ser verdaderas,
    justificar, en caso de ser falsas poner un contraejemplo:

    {:.lower_alpha}
    1. Si dos árboles binarios tienen el mismo recorrido inorder, entonces tienen la misma
    estructura.

    1. Si dos árboles binarios tienen el mismo recorrido preorder, entonces tienen la misma
    estructura.

    1. Si dos árboles binarios de búsqueda (e idéntica función de comparación) tienen el mismo
    recorrido preorder, entonces tienen la misma estructura.

1.  (★★) Implementar una primitiva para el ABB, que reciba el ABB y devuelva una lista con las claves
    del mismo, ordenadas tal que si insertáramos las claves en un ABB vacío (con la misma función
    de comparación), dicho ABB tendría la misma estructura que el árbol original. ¿Qué tipo de
    recorrido utilizaste? Indicar y justificar el orden de la primitiva.

1.  (★★★★) Implementar una primitiva para el AB que reciba dos arreglos (o listas) de cadenas. El primer arreglo
    corresponde al preorder de un árbol binario. El segundo al inorder del mismo árbol (ambos arreglos
    tienen los mismos elementos, sin repetidos). La función debe devolver un árbol binario que tenga dicho
    preorder e inorder. Indicar y justificar el orden de la primitiva (tener cuidado con este punto).
    Considerar que la estructura del árbol binario es:

    ```golang
        type Arbol struct {
            izq *Arbol
            der *Arbol
        }
    ```


1.  (★★★★) Implementar una función que reciba un arreglo ordenado y devuelva un arreglo o lista con
    los elementos en orden para ser insertados en un ABB, de tal forma que al insertarlos en
    dicho orden se asegure que el ABB quede balanceado. ¿Cómo cambiarías tu resolución si en
    vez de querer guardarlos en un ABB se fueran a insertar en un AVL?

1.  (★★★) Determinar cómo es el Árbol cuyo pre order es `EURMAONDVSZT`, e in order es `MRAUOZSVDNET`, e 
    indicar su recorrido post order.
    
1.  (★★★) En un árbol binario, dado un nodo con dos hijos, explicar por qué su predecesor en el recorrido 
    inorder no puede tener hijo derecho, y que su sucesor (también, en el recorrido inorder) no puede tener 
    hijo izquierdo.
    
1.  (★★) Implementar en Go una **primitiva** de ABB (DiccionarioOrdenado) que funcione 
    como un iterador interno que haga un recorrido por niveles inverso. Es decir, que visite 
    los elementos del nivel más inferior hasta la raiz. Para el ABB cuyo preorder es
    `5, 2, 1, 3, 4, 7, 9` (comparación numérica habitual), el recorrido debe ser: 
    `4, 9, 3, 1, 7, 2, 5`. En el 4to nivel está sólo el `4`. En el 3er nivel están el `1, 3 y 9` pero hay 
    que leerlos de derecha a izquierda.
    Luego en el 2do el `2 y 7` con la misma lógica, y finalmente la raíz `5` al final.
    Indicar y justificar la complejidad de la primitiva implementada.
