#include "usuarios.h"

int carregar_usuarios(char nome_arquivo_usuarios[], usuario lista_usuarios[]) {
    FILE *arquivo_usuarios;
    arquivo_usuarios = fopen(nome_arquivo_usuarios, "r");
    if (arquivo_usuarios == NULL) {
        return 0;
    }
    int i = 0;
    while(fscanf(arquivo_usuarios, "%49[^;];%d;%d;%14[^;]\n", lista_usuarios[i].nome, &lista_usuarios[i].ano_nascimento, &lista_usuarios[i].matricula, lista_usuarios[i].tipo) == 4) {
        i++;
    }
    fclose(arquivo_usuarios);
    return i;
}

void cadastrar_usuario(char nome_arquivo_usuarios[], usuario lista_usuarios[], int total_usuarios_cadastrados) {
    FILE *arquivo_usuarios;
    int total_usuarios_a_cadastrar;
    arquivo_usuarios = fopen(nome_arquivo_usuarios, "w");
    if (arquivo_usuarios == NULL) {
        printf("Erro ao cadastrar usuario\n");
        return;
    }
    if (total_usuarios_cadastrados >= 2) {
        printf("%d usuarios cadastrados ate o momento\n", total_usuarios_cadastrados);
    } else if (total_usuarios_cadastrados == 1) {
        printf("%d usuario cadastrado ate o momento\n", total_usuarios_cadastrados);
    } else {
        printf("Nenhum usuario cadastrado ate o momento\n");
    }
    printf("Quantos usuarios deseja cadastrar: ");
    scanf("%d", &total_usuarios_a_cadastrar);
    if (total_usuarios_a_cadastrar + total_usuarios_cadastrados >= 50) {
        printf("Voce atingiu o limite de cadastro de usuarios\n");
        printf("Limite de usuarios: %d\n", MAX_USUARIOS);
        printf("Ao tentar cadastrar %d usuarios, o total sera de %d usuarios\n", total_usuarios_a_cadastrar, total_usuarios_a_cadastrar + total_usuarios_cadastrados);
        printf("Tente cadastrar ate %d usuarios\n", MAX_USUARIOS - total_usuarios_cadastrados);
    }
    if (total_usuarios_a_cadastrar <= 0) {
        printf("Cadastro encerrado\n");
        return;
    }
}