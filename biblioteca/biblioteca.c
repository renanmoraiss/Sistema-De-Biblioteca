#include "biblioteca.h"

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
    if (total_livros_a_cadastrar + total_livros_cadastrados >= 100) {
        printf("Voce atingiu o limite de cadastro de livros\n");
        printf("Ao tentar cadastrar %d livros, o total sera de %d livros\n", total_livros_a_cadastrar, total_livros_a_cadastrar + total_livros_cadastrados);
        printf("Tente cadastrar ate %d livros\n", MAX_LIVROS - total_livros_cadastrados);
        return;
    }
    if (total_livros_a_cadastrar <= 0) {
        printf("Cadastro encerrado\n");
        return;
    }
    int contagem_de_livros_para_cadastrar = 0;
    int indice_livro_encontrado;
    int alerta_problema_livro_repetido = 0;
    for (int i = total_livros_cadastrados; i < total_livros_cadastrados + total_livros_a_cadastrar && contagem_de_livros_para_cadastrar < total_livros_a_cadastrar; i++) {
        if (alerta_problema_livro_repetido == 1) {
            printf("!!! TENTE NOVAMENTE !!!\n");
        }
        printf("Titulo: ");
        scanf(" %49[^\n]", lista_livros[i].titulo);
        if (total_livros_cadastrados > 0) {
            indice_livro_encontrado = verificar_livro_existente(lista_livros[i].titulo, lista_livros, total_livros_cadastrados);
            //
            if (indice_livro_encontrado >= 0) {
                printf("===== PROBLEMA AO CADASTRAR LIVRO =====\n");
                printf("O livro '%s' ja esta cadastrado com %d exemplares\n", lista_livros[indice_livro_encontrado].titulo, lista_livros[indice_livro_encontrado].exemplares);
                alerta_problema_livro_repetido = 1;
                continue;
            } else {
                contagem_de_livros_para_cadastrar++;
            }
        }        

        printf("Codigo: ");
        scanf("%d", &lista_livros[i].codigo);

        printf("Autor: ");
        scanf(" %49[^\n]", lista_livros[i].autor);

        printf("Ano de lancamento: ");
        scanf("%d", &lista_livros[i].ano);

        printf("Total de exemplares: ");
        scanf("%d", &lista_livros[i].exemplares);

        fprintf(arquivo_livro, "%d;%s;%s;%d;%d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
    }
    //
    fclose(arquivo_livro);
    //
    if (contagem_de_livros_para_cadastrar == 0) {
        printf("Nenhum livro cadastrado\n");
    } else if (contagem_de_livros_para_cadastrar > 0) {
        printf("%d livro(s) cadastrado(s)\n", contagem_de_livros_para_cadastrar);
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
    if (total_livros_cadastrados == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    for (int i = 0; i < total_livros_cadastrados; i++) {
        printf("%d; %s; %s; %d; %d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
    }
}

void buscar_livro(livro lista_livros[], int total_livros_cadastrados) {
    if (total_livros_cadastrados == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
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

void editar_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados) {
    if (total_livros_cadastrados == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    char titulo_livro_para_editar[50];
    int opc_escolhida;
    char titulo_edicao[50];
    char autor_edicao[50];
    int ano_edicao;
    int exemplares_edicao;
    FILE *arquivo_livro;
    arquivo_livro = fopen(nome_arquivo_livros, "r");
    if (arquivo_livro == NULL) {
        return;
    }
    printf("Qual o titulo do livro que deseja editar: ");
    scanf(" %49[^\n]", titulo_livro_para_editar);
    int livro_encontrado_para_editar = 0;
    int identificador_livro;
    for (int i = 0; i < total_livros_cadastrados && livro_encontrado_para_editar == 0; i++) {
        if (strcmp(titulo_livro_para_editar, lista_livros[i].titulo) == 0) {
            identificador_livro = i;
            livro_encontrado_para_editar = 1;
        }
    }
    if (livro_encontrado_para_editar == 1) {
        printf("===== EDITAR O LIVRO '%s' =====\n", lista_livros[identificador_livro].titulo);
        printf("1. Editar titulo\n");
        printf("2. Editar autor\n");
        printf("3. Editar ano\n");
        printf("4. Editar numero de exemplares\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc_escolhida);
    } else {
        printf("O livro '%s' nao foi encontrado\n", titulo_livro_para_editar);
        return;
    }

    //
    if ((opc_escolhida >= 1) && (opc_escolhida <= 4)) {
        switch(opc_escolhida) {
            case 1:
            printf("Novo titulo: ");
            scanf(" %49[^\n]", titulo_edicao);
            strcpy(lista_livros[identificador_livro].titulo, titulo_edicao);
            break;

            case 2:
            printf("Novo autor: ");
            scanf(" %49[^\n]", autor_edicao);
            strcpy(lista_livros[identificador_livro].autor, autor_edicao);
            break;

            case 3:
            printf("Novo ano: ");
            scanf("%d", &ano_edicao);
            lista_livros[identificador_livro].ano = ano_edicao;
            break;

            case 4:
            printf("Novo numero de exemplares: ");
            scanf("%d", &exemplares_edicao);
            lista_livros[identificador_livro].exemplares = exemplares_edicao;
            break;
        }
        fclose(arquivo_livro);
        arquivo_livro = fopen(nome_arquivo_livros, "w");
        if (arquivo_livro == NULL) {
            return;
        }
        for (int i = 0; i < total_livros_cadastrados; i++) {
            fprintf(arquivo_livro, "%d;%s;%s;%d;%d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
        }
        fclose(arquivo_livro);
    }
}

void excluir_livro(char nome_arquivo_livros[], livro lista_livros[], int total_livros_cadastrados) {
    if (total_livros_cadastrados == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    FILE *arquivo_livro;
    FILE *arquivo_livro_temp;
    char nome_arquivo_livros_temp[30] = "livrostemp.txt";
    char titulo_livro_exclusao[50];
    int livro_encontrado = 0;
    int indice_livro_excluir = 0;
    arquivo_livro = fopen(nome_arquivo_livros, "r");
    if (arquivo_livro == NULL) {
        return;
    }
    printf("Qual o titulo do livro que deseja excluir: ");
    scanf(" %49[^\n]", titulo_livro_exclusao);
    for (int i = 0; i < total_livros_cadastrados && livro_encontrado != 1; i++) {
        if (strcmp(titulo_livro_exclusao, lista_livros[i].titulo) == 0) {
            indice_livro_excluir = i;
            livro_encontrado = 1;
        }
    }
    if (livro_encontrado == 1) {
        arquivo_livro_temp = fopen(nome_arquivo_livros_temp, "w");
        if (arquivo_livro_temp == NULL) {
            return;
        }
        for (int i = 0; i < total_livros_cadastrados; i++) {
            if (i != indice_livro_excluir) {
                fprintf(arquivo_livro_temp, "%d;%s;%s;%d;%d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
            }
        }
        fclose(arquivo_livro);
        fclose(arquivo_livro_temp);
        
        arquivo_livro = fopen(nome_arquivo_livros, "w");
        if (arquivo_livro == NULL) {
            return;
        }
        arquivo_livro_temp = fopen(nome_arquivo_livros_temp, "r");
        if (arquivo_livro_temp == NULL) {
            return;
        }

        int i = 0;
        while (fscanf(arquivo_livro_temp, "%d;%49[^;];%49[^;];%d;%d\n", &lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, &lista_livros[i].ano, &lista_livros[i].exemplares) == 5) {
            if (lista_livros[i].codigo > indice_livro_excluir) {
                lista_livros[i].codigo = lista_livros[i].codigo - 1;
            }
            fprintf(arquivo_livro, "%d;%s;%s;%d;%d\n", lista_livros[i].codigo, lista_livros[i].titulo, lista_livros[i].autor, lista_livros[i].ano, lista_livros[i].exemplares);
            i++;
        }

        fclose(arquivo_livro);
        fclose(arquivo_livro_temp);
        remove(nome_arquivo_livros_temp);

    } else {
        fclose(arquivo_livro);
        printf("O livro '%s' nao foi encontrado\n", titulo_livro_exclusao);
        return;
    }
}