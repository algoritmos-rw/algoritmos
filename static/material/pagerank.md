---
layout: default
title: PageRank
permalink: /material/pagerank
math: true
---

# PageRank

El algoritmo de [PageRank](http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf), creado por Sergey Brin y 
Larry Page, nos permite definir un ranking, o importancia, de los distintos vértices dentro de una red. 
Esto es similar a lo que busca obtener [la centralidad de un grafo](centralidad), si bien distintas
centralidades pueden servir para objetivos diferentes. Este algoritmo fue el inicialmente utilizado
por el _engine_ de Google para rankear sus búsquedas de páginas webs. 

Éste algoritmo implica calcular: 

$$ \text{PR}\left(p_i\right) = \frac{1-d}{N} + d \sum_{p_j \in M\left(p_i\right)} 
\frac{\text{PR}\left(p_j\right)}{L\left(p_j\right)} $$

Donde:
* $$\text{PR}\left(p_i\right)$$: Pagerank del artículo (vértice) $$p_i$$ que se está queriendo calcular.
* $$d$$: coeficiente de amortiguación. 
* $$N$$: cantidad de artículos (vértices). **Ciudado**: tanto en el paper original, como en el artículo de
Wikipedia en español no aparece este término, que es muy importante para que el valor del pagerank se
mantenga entre 0 y 1. 
* $$\text{PR}\left(p_j\right)$$: pagerank del artículo $$p_j$$, donde $$p_j$$ sea un artículo que tenga un
link hacia $$p_i$$. Se consideran todos los artículos que tengan un link hacia $$p_i$$.
* $$L\left(p_j\right)$$: cantidad de links que tiene el artículo $$j$$ (mismo que 
$$\text{PR}\left(p_j\right)$$).


El valor del Pagerank puede verse intuitivamente como la probabilidad de aparecer en un articulo navegando
a través de internet, ya sea yendo a través de los links (segundo término) o accediendo de forma aleatoria 
(primer término).
