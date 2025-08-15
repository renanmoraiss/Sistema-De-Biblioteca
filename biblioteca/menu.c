#include "menu.h"

int menu() {
    int opcao_escolhida;
    printf("===== SISTEMA DE BIBLIOTECA =====\n");
    printf("1. Cadastrar livro\n");
    printf("2. Listar livros\n");
    printf("3. Buscar livro\n");
    printf("4. Editar livro\n");
    printf("5. Excluir livro\n");
    printf("6. Encerrar sistema\n");
    printf("-----\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao_escolhida);
    if (opcao_escolhida >= 1 && opcao_escolhida <= 6) {
        return opcao_escolhida;
    } else {
        printf("A opcao '%d' nao existe!\n", opcao_escolhida);
        return -1;
    }
}

void encerrar_sistema() {
    printf("Sistema encerrado!\n");
    return;
}