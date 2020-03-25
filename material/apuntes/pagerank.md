---
math: true
---

# PageRank

El algoritmo de [PageRank](http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf), creado por Sergey Brin y
Larry Page, nos permite definir un ranking, o importancia, de los distintos vértices dentro de una red.
Esto es similar a lo que busca obtener [la centralidad de un grafo](centralidad.md), si bien distintas
centralidades pueden servir para objetivos diferentes. Este algoritmo fue el inicialmente utilizado
por el _engine_ de Google para rankear sus búsquedas de páginas webs.

Éste algoritmo implica calcular:

$$
\text{PR}\left(p_i\right) = \frac{1-d}{N} + d \sum_{p_j \in M\left(p_i\right)}
\frac{\text{PR}\left(p_j\right)}{L\left(p_j\right)}
$$

Donde:
* $$\text{PR}\left(p_i\right)$$: Pagerank del artículo (vértice) $$p_i$$ que se está queriendo calcular.
* $$d$$: coeficiente de amortiguación (valor entre 0 y 1). Representa la probabilidad de seguir yendo de
página en página utilizando links, en vez de escribir una URL en el browser.
* $$N$$: cantidad de artículos (vértices). **Ciudado**: En el paper original no aparece este término, que
es muy importante para que el valor del pagerank se mantenga entre 0 y 1. La explicación de éste error se
encuentra en [el artículo de Wikipedia en inglés](https://en.wikipedia.org/wiki/PageRank) (en el artículo
en español mantiene el error).
* $$\text{PR}\left(p_j\right)$$: pagerank del artículo $$p_j$$, donde $$p_j$$ sea un artículo que tenga un
link hacia $$p_i$$. Se consideran todos los artículos que tengan un link hacia $$p_i$$. Es importante notar
que cuando se trata de un grafo dirigido, estamos hablando de las aristas de entrada a $$p_i$$, no las de
salida.
* $$L\left(p_j\right)$$: cantidad de links que tiene el artículo $$j$$ (mismo que
$$\text{PR}\left(p_j\right)$$).


El valor del Pagerank puede verse intuitivamente como la probabilidad de aparecer en un articulo navegando
a través de internet, ya sea yendo a través de los links (segundo término) o accediendo de forma aleatoria
(primer término).

Es necesario realizar varias iteraciones de este algoritmo para que termine por converger y que la
actualización sea asincrónica (todos tomando los valores de la iteración anterior).
