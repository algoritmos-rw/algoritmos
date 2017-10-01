# Flags de gcc. Se usan automáticamente para compilar *.c → *.o
CFLAGS := -g -std=c99 -Wall -Werror -Wformat=2 -MMD
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

# Si se ejecuta `make` a secas, se compilarán tac, tail y strutil.
all: tac tail strutil.o

# Se puede escribir `make tac`, `make tail` o `make strutil.o` para compilar
# una parte del TP solamente.
tac: tac.o
tail: tail.o

# Si tac o tail usan un TDA, se debe especificar bien en las lineas anteriores,
# bien aquí. Ejemplos:

# tac: cola.o
# tac: pila.o
# tail: lista.o
# tail: cola.o

clean::
	rm -f tac tail *.o *.d

-include $(SRCS:%.c=%.d)

.PHONY: all clean
