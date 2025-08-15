#include "biblioteca.h"
#include "menu.h"

int main() {
    livro lista_livros[MAX_LIVROS];
    int total_livros;
    int opcao_menu_escolhida;
    char nome_arquivo_livros[30] = "livros.txt";
    total_livros = carregar_livros(nome_arquivo_livros, lista_livros);
    do {
        opcao_menu_escolhida = menu();
        switch(opcao_menu_escolhida) {

        case 1:
        cadastrar_livro(nome_arquivo_livros, lista_livros, total_livros);
        total_livros = carregar_livros(nome_arquivo_livros, lista_livros);
        break;

        case 2:
        listar_livros(lista_livros, total_livros);
        break;

        case 3:
        buscar_livro(lista_livros, total_livros);
        break;

        case 4:
        editar_livro(nome_arquivo_livros, lista_livros, total_livros);
        break;

        case 5:
        excluir_livro(nome_arquivo_livros, lista_livros, total_livros);
        total_livros = carregar_livros(nome_arquivo_livros, lista_livros);
        break;

        case 6:
        encerrar_sistema();
        break;
    }
    } while(opcao_menu_escolhida != 6);
    return 0;
}