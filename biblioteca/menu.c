#include "menu.h"

int menu() {
    int chosen_option;
    printf("===== SISTEMA DE BIBLIOTECA =====\n");
    printf("1. Cadastrar livro\n");
    printf("2. Listar livros\n");
    printf("3. Buscar livro\n");
    printf("4. Editar livro\n");
    printf("5. Excluir livro\n");
    printf("6. Encerrar sistema\n");
    printf("-----\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &chosen_option);
    if (chosen_option >= 1 && chosen_option <= 6) {
        return chosen_option;
    } else {
        printf("A opcao '%d' nao existe!\n", chosen_option);
        return -1;
    }
}

void close_system() {
    printf("Sistema encerrado!\n");
    return;
}