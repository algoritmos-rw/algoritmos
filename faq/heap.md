# FAQ - Heap
{:.no_toc}

* Contenido
{:toc}

## ¿Por qué no representamos heaps con nodos enlazados?
Los heaps son árboles completos, por lo que si se representa la estructura con un arreglo se pueden calcular de manera sencilla y elegante las posiciones de los padres e hijos de cada nodo. De esta manera los algoritmos resultan muy fáciles de programar y se evita la creación y el encadenamiento de los nodos en cada operación de alta o baja. Además, se ahorra memoria ya que no es necesario almacenar referencias entre nodos.
