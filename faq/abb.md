# FAQ - Árbol Binario de Búsqueda
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo se destruye un dato en un ABB?

Recomendamos seguir este algoritmo para destruir datos en un árbol binario de búsqueda: después de localizar el nodo a eliminar se consideran tres casos:
  - Si el nodo es una hoja (es decir: no tiene hijos), se elimina.
  - Si el nodo tiene un solo hijo, se elimina el nodo y se reemplaza con su hijo.
  - Si el nodo tiene dos hijos no se elimina el nodo, sino que se reemplaza con el siguiente inorder (es decir, con el menor de sus hijos mayores) o con el anterior inorder (el mayor de sus hijos menores).

Luego se llama a la eliminación recursiva en el subárbol correspondiente de acuerdo a la estrategia de eliminación elegida. Como se eligió o bien el menor de sus hijos mayores o el mayor de sus hijos menores, obligatoriamente al nodo a borrar le va a faltar un hijo, haciendo que se caiga en alguno de los dos primeros casos.
