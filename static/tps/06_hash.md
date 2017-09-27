---
layout: page
title: Hash
permalink: /tps/hash
---

Tabla de Hash
=============

Para el viernes 06 de octubre deben entregar de forma grupal el tipo abstracto de datos Tabla de Hash, que se puede implementar mediante un hash abierto o cerrado, a elección.

#### Primitivas del hash
``` cpp
typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;
typedef void (*hash_destruir_dato_t)(void *);

hash_t *hash_crear(hash_destruir_dato_t destruir_dato);
bool hash_guardar(hash_t *hash, const char *clave, void *dato);
void *hash_borrar(hash_t *hash, const char *clave);
void *hash_obtener(const hash_t *hash, const char *clave);
bool hash_pertenece(const hash_t *hash, const char *clave);
size_t hash_cantidad(const hash_t *hash);
void hash_destruir(hash_t *hash);
```

#### Primitivas del iterador
``` cpp
hash_iter_t *hash_iter_crear(const hash_t *hash);
bool hash_iter_avanzar(hash_iter_t *iter);
const char *hash_iter_ver_actual(const hash_iter_t *iter);
bool hash_iter_al_final(const hash_iter_t *iter);
void hash_iter_destruir(hash_iter_t* iter);
```

El iterador debe permitir recorrer todos los elementos almacenados en el hash, sin importar el orden en el que son devueltos.

Se adjunta, además, un archivo de pruebas que pueden utilizar para verificar que la estructura funciona correctamente.  El corrector automático, igualmente, añade más pruebas.

Al igual que para las entregas anteriores, deberán entregar el código en papel, con el nombre y padrón de los integrantes del grupo, imprimiendo los archivos `hash.h` y `hash.c`.   

Además, deben subir el código a la [página de entregas de la materia](https://algoritmos7541-rw.tk/entregas/), con el código completo.

