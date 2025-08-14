#ifndef USUARIOS.H
#define USUARIOS.H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USUARIOS 50

struct Usuario {
    char nome[50];
    int ano_nascimento;
    int matricula;
    char tipo[15];
};

typedef struct Usuario usuario;

#endif