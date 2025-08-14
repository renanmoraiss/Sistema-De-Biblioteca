#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIVROS 100

struct Livro {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
    int exemplares;
};

typedef struct Livro livro;

int menu();
int carregar_livros(char nome_arquivo_livros[], livro lista_livros[]);
void cadastrar_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados);
int verificar_livro_existente(char titulo_livro_digitado[], livro lista_livros[], int total_livros_cadastrados);
void listar_livros(livro lista_livros[], int total_livros_cadastrados);
void buscar_livro(livro lista_livros[], int total_livros_cadastrados);
void buscar_livro_codigo(livro lista_livros[], int codigo_busca, int total_livros_cadastrados);
void buscar_livro_titulo(livro lista_livros[], char titulo_busca[], int total_livros_cadastrados);
void buscar_livro_autor(livro lista_livros[], char autor_busca[], int total_livros_cadastrados);
void buscar_livro_ano(livro lista_livros[], int ano_busca, int total_livros_cadastrados);
void editar_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados);
void excluir_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados);
void encerrar_sistema();

#endif