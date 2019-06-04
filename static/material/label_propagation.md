---
layout: default
title: Comunidades y Label Propagation
permalink: /material/label_propagation
math: true
---

# Comunidades en un grafo

Un problema común dentro de grafos que representan redes sociales es querer obtener las comunidades que 
la conforman. Una comunidad dentro de una red social es un conjunto de vértices que se encuentran altamente
conectados entre sí, y poco conectados con los vértices de afuera. Este es un problema que está abarcado
por el área de Aprendizaje No Supervisado ([Clustering](https://en.wikipedia.org/wiki/Cluster_analysis))
dentro de Aprendizaje Automático. 

Como estos temas no están incluidos dentro de los contenidos de la materia, usaremos un algoritmo sencillo
que suele encontrar muy buenos resultados: [Label Propagation](http://arxiv.org/pdf/0709.2938v1.pdf). 
Dicho algoritmo es utilizado, por ejemplo, en Facebook para realizar inferencias.

## Label Propagation

En label propagation lo que hacemos es:

1. Para cada vértice $$V_i$$: $$Label[V_i] = i$$

1. Determinar un orden aleatorio para los vértices.

1. Por cada vértice, en el orden determinado en el punto anterior, definir: $$Label[V_i] = max\_freq(Label[V_j], ..., Label[V_k])$$.
Donde $$V_j, ..., V_k$$ son los vértices adyacentes a $$V_i$$. Se tiene en cuenta la última actualización
realizada, inclusive si ya fueron procesados en esta iteración (actualización ascincrónica). 
$$max\_freq$$ es una función que devuelve la $$Label$$ que aparece más frecuentemente entre todos los 
adyacentes a $$V_i$$. En caso de empate, es igual cual de los máximos devolver. 

1. Si no se llegó a la condición de corte, volver a 2. La condición de corte puede ser una vez que se llegó 
a una cantidad determinada de comunidades, se cree que se llegó a la convergencia (la mayoría de los
vecinos de cada vértice tiene la misma Label que dicho vértice), o simplemente por una cantidad de
iteraciones prefijada.

Como opción alternativa, brindamos otro algoritmo que utiliza [Random Walks](random_walks) para obtener 
las posibles comunidades: 
[Entropy Walker](https://drive.google.com/file/d/0B8rBD4QSqWnSLTdWTXdFaUtUNjQ/view).

