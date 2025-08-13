#include "biblioteca.h"

int menu() {
    int opcao_escolhida;
    printf("===== SISTEMA DE BIBLIOTECA =====\n");
    printf("1. Cadastrar livro\n");
    printf("2. Listar livros\n");
    printf("3. Buscar livro\n");
    printf("4. Cadastrar usuario\n");
    printf("5. Listar usuarios\n");
    printf("6. Realizar emprestimo\n");
    printf("7. Realizar devolucao\n");
    printf("8. Relatorios\n");
    printf("9. Encerrar\n");
    printf("-----\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao_escolhida);
    if (opcao_escolhida >= 1 && opcao_escolhida <= 9) {
        return opcao_escolhida;
    } else {
        printf("Opcao escolhida nao existe\n");
        return -1;
    }
}

int carregar_livros(char nome_arquivo_livros[], livro lista_livros[]) {
    FILE *arquivo_livro;
    arquivo_livro = fopen(nome_arquivo_livros, "r");
    if (arquivo_livro == NULL) {
        return 0;
    }
    int i = 0;
    while (fscanf(arquivo_livro, "%d;%49[^;];%49[^;];%d;%d", &lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, &lista_livros[i].ano, &lista_livros[i].exemplares) == 5) {
        i++;
    }
    fclose(arquivo_livro);
    return i;
}

void cadastrar_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados) {
    FILE *arquivo_livro;
    int total_livros_a_cadastrar;
    arquivo_livro = fopen(nome_arquivo_livros, "a");
    if (arquivo_livro == NULL) {
        printf("Erro ao cadastrar livro\n");
        return;
    }
    if (total_livros_cadastrados >= 2) {
        printf("%d livros cadastrados ate o momento\n", total_livros_cadastrados);
    } else if (total_livros_cadastrados == 1) {
        printf("%d livro cadastrado ate o momento\n", total_livros_cadastrados);
    } else {
        printf("Nenhum livro cadastrado ate o momento\n");
    }
    printf("Quantos livros deseja cadastrar: ");
    scanf("%d", &total_livros_a_cadastrar);
    if (total_livros_a_cadastrar <= 0) {
        printf("Cadastro encerrado\n");
        return;
    }
    int indice_livro_encontrado;
    int livro_duplicado = 0;
    int livro_cadastrado = 0;
    for (int i = total_livros_cadastrados; i < total_livros_cadastrados + total_livros_a_cadastrar; i++) {
        printf("Titulo: ");
        scanf(" %49[^\n]", lista_livros[i].titulo);
        if (total_livros_cadastrados > 0) {
            indice_livro_encontrado = verificar_livro_existente(lista_livros[i].titulo, lista_livros, total_livros_cadastrados);
            //
            if (indice_livro_encontrado >= 0) {
                printf("===== PROBLEMA AO CADASTRAR LIVRO =====\n");
                printf("O livro '%s' ja esta cadastrado com %d exemplares\n", lista_livros[indice_livro_encontrado].titulo, lista_livros[indice_livro_encontrado].exemplares);
                livro_duplicado++;
                continue;
            }
        }

        printf("Codigo: ");
        scanf("%d", &lista_livros[i].codigo);

        printf("Autor: ");
        scanf(" %49[^\n]", lista_livros[i].autor);

        printf("Ano: ");
        scanf("%d", &lista_livros[i].ano);

        printf("Exemplares: ");
        scanf("%d", &lista_livros[i].exemplares);

        fprintf(arquivo_livro, "%d;%s;%s;%d;%d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        livro_cadastrado++;
    }
    //
    fclose(arquivo_livro);
    //
    if ((livro_cadastrado == total_livros_a_cadastrar) && (livro_duplicado == 0)) {
        printf("Livro(s) cadastrado(s) com sucesso\n");
    }
}

int verificar_livro_existente(char titulo_livro_digitado[], livro lista_livros[], int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        if (strcmp(titulo_livro_digitado, lista_livros[i].titulo) == 0) {
            return i;
        }
    }
    return -1;
}

void listar_livros(livro lista_livros[], int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
    }
}

void buscar_livro(livro lista_livros[], int total_livros_cadastrados) {
    int forma_de_busca_escolhida;
    int codigo_busca;
    int ano_busca;
    char titulo_busca[50];
    char autor_busca[50];
    printf("===== SISTEMA DE BUSCA =====\n");
    printf("1. Buscar pelo codigo\n");
    printf("2. Buscar pelo titulo\n");
    printf("3. Buscar pelo autor\n");
    printf("4. Buscar pelo ano\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &forma_de_busca_escolhida);
    if ((forma_de_busca_escolhida >= 1) && (forma_de_busca_escolhida <= 4)) {
        switch(forma_de_busca_escolhida) {
            case 1:
            printf("Codigo para buscar: ");
            scanf("%d", &codigo_busca);
            buscar_livro_codigo(lista_livros, codigo_busca, total_livros_cadastrados);
            break;

            case 2:
            printf("Titulo para buscar: ");
            scanf(" %49[^\n]", titulo_busca);
            buscar_livro_titulo(lista_livros, titulo_busca, total_livros_cadastrados);
            break;

            case 3:
            printf("Autor para buscar: ");
            scanf(" %49[^\n]", autor_busca);
            buscar_livro_autor(lista_livros, autor_busca, total_livros_cadastrados);
            break;

            case 4:
            printf("Ano para buscar: ");
            scanf("%d", &ano_busca);
            buscar_livro_ano(lista_livros, ano_busca, total_livros_cadastrados);
            break;
        }
    } else {
        printf("Opcao escolhida nao existe\n");
        return;
    }
}

void buscar_livro_codigo(livro lista_livros[], int codigo_busca, int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        if (lista_livros[i].codigo == codigo_busca) {
            printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        }
    }
}

void buscar_livro_titulo(livro lista_livros[], char titulo_busca[], int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        if (strcmp(titulo_busca, lista_livros[i].titulo) == 0) {
            printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        }
    }
}

void buscar_livro_autor(livro lista_livros[], char autor_busca[], int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        if (strcmp(autor_busca, lista_livros[i].autor) == 0) {
            printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        }
    }
}

void buscar_livro_ano(livro lista_livros[], int ano_busca, int total_livros_cadastrados) {
    for (int i = 0; i < total_livros_cadastrados; i++) {
        if (ano_busca == lista_livros[i].ano) {
            printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        }
    }
}

void encerrar_sistema() {
    printf("Sistema encerrado\n");
    return;
}