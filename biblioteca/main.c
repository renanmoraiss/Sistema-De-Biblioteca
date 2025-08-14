#include "biblioteca.h"
#include "usuarios.h"
#include "menu.h"

int main() {
    livro lista_livros[MAX_LIVROS];
    usuario lista_usuarios[MAX_USUARIOS];
    int total_livros;
    int total_usuarios;
    int opcao_menu_escolhida;
    char nome_arquivo_livros[30] = "livros.txt";
    char nome_arquivo_usuarios[30] = "usuarios.txt";
    total_livros = carregar_livros(nome_arquivo_livros, lista_livros);
    total_usuarios = carregar_usuarios(nome_arquivo_usuarios, lista_usuarios);
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
        cadastrar_usuario(nome_arquivo_usuarios, lista_usuarios, total_usuarios);
        total_usuarios = carregar_usuarios(nome_arquivo_usuarios, lista_usuarios);
        break;

        case 14:
        encerrar_sistema();
        break;
    }
    } while(opcao_menu_escolhida != 14);
    return 0;
}