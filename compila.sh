#!/bin/bash

#compila libreria.c en un archivo objeto
gcc -Werror -Wall -Wextra -c libreria.c -o libreria.o

#crea la biblioteca estatica libreria.a
ar -rv liblibreria.a libreria.o

#compila test.c y enlaza con la biblioteca libreria.a
gcc test.c -Werror -Wall -Wextra -o test -L. -llibreria

echo "Compilacion completada.Ejecuta ./test para probar"



