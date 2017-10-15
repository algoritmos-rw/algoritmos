---
layout: post
title: "Actualizado el enunciado del TP1"
date: 2017-10-08 13:30:00 -0300
---

Ha sido actualizado el [enunciado del TP1]({{ 'tps/2017_2/tp1' | relative_url }})
para clarificar algunos aspectos y especificar otros que no estaban.


Resumen de cambios:

- Se [agrega un ejemplo]({{ 'tps/2017_2/tp1#con-impresión-de-pagos-pendientes' | relative_url  }})
y se especifica cómo se imprimen los [pagos pendientes]({{ 'tps/2017_2/tp1#interfaz' | relative_url }}).
- Se [agrega un ejemplo]({{ 'tps/2017_2/tp1#con-un-comando-inexistente' | relative_url  }})
y se [especifica el comportamiento]({{ 'tps/2017_2/tp1#manejo-de-errores-y-precondiciones' | relative_url  }})
cuando se ingresa un comando no válido (ahora es un error de tipo 2).
- Se [especifica el orden]({{ 'tps/2017_2/tp1#manejo-de-errores-y-precondiciones' | relative_url  }})
de la impresión del resultado OK.
- Se [deja a libre elección]({{ 'tps/2017_2/tp1#manejo-de-errores-y-precondiciones' | relative_url  }})
el comportamiento ante errores de tipo 1.
- Se aclara en los dos ejemplos que las salida son por streams diferentes
([[1]]({{ 'tps/2017_2/tp1#con-un-código-de-pago-inválido' | relative_url }})
y [[2]]({{ 'tps/2017_2/tp1#con-un-comando-inválido' | relative_url }})).
- Se [aclara]({{ 'tps/2017_2/tp1#criterios-de-aprobación' | relative_url }}}})
 el formato de `deps.mk` y los flags del corrector a ser usados.
- Se agrega una [recomendación]({{ 'tps/2017_2/tp1#interfaz' | relative_url }})
del formato de impresión de números decimales.

Se pueden visualizar todos los cambios [aquí](https://github.com/algoritmos-rw/algo2/pull/35/files).