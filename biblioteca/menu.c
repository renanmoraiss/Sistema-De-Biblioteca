#include "menu.h"

int menu() {
    int opcao_escolhida;
    printf("===== SISTEMA DE BIBLIOTECA =====\n");
    printf("1. Cadastrar livro\n");
    printf("2. Listar livros\n");
    printf("3. Buscar livro\n");
    printf("4. Editar livro\n");
    printf("5. Excluir livro\n");
    printf("6. Cadastrar usuario\n");
    printf("7. Listar usuarios\n");
    printf("8. Buscar usuario\n");
    printf("9. Editar usuario\n");
    printf("10. Excluir usuario\n");
    printf("11. Realizar emprestimo\n");
    printf("12. Realizar devolucao\n");
    printf("13. Relatorios\n");
    printf("14. Encerrar\n");
    printf("-----\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao_escolhida);
    if (opcao_escolhida >= 1 && opcao_escolhida <= 14) {
        return opcao_escolhida;
    } else {
        printf("Opcao escolhida nao existe\n");
        return -1;
    }
}

void encerrar_sistema() {
    printf("Sistema encerrado\n");
    return;
}