#include "library.h"

int load_books(char file_name_books[], book list_books[]) {
    FILE *book_file;
    book_file = fopen(file_name_books, "r");
    if (book_file == NULL) {
        return 0;
    }
    int i = 0;
    while (fscanf(book_file, "%d;%49[^;];%49[^;];%d;%d", &list_books[i].code, list_books[i].title, list_books[i].author, &list_books[i].year, &list_books[i].copies) == 5) {
        i++;
    }
    fclose(book_file);
    return i;
}

void register_book(char file_name_books[], book list_books[], int total_registered_books) {
    FILE *book_file;
    int total_of_books_to_register;
    book_file = fopen(file_name_books, "a");
    if (book_file == NULL) {
        return;
    }
    if (total_registered_books >= 2) {
        printf("%d livros cadastrados ate o momento\n", total_registered_books);
    } else if (total_registered_books == 1) {
        printf("%d livro cadastrado ate o momento\n", total_registered_books);
    } else {
        printf("Nenhum livro cadastrado ate o momento\n");
    }
    printf("Quantos livros deseja cadastrar: ");
    scanf("%d", &total_of_books_to_register);
    if (total_of_books_to_register + total_registered_books >= 100) {
        printf("Voce atingiu o limite de cadastro de livros\n");
        printf("Ao tentar cadastrar %d livros, o total sera de %d livros\n", total_of_books_to_register, total_of_books_to_register + total_registered_books);
        printf("Tente cadastrar ate %d livros\n", MAX_BOOKS - total_registered_books);
        return;
    }
    if (total_of_books_to_register <= 0) {
        printf("Nao eh possivel cadastrar %d livro(s)\n", total_of_books_to_register);
        printf("Cadastro encerrado\n");
        return;
    }
    int counter = 0;
    int repeated_book_index;
    int repeated_book = 0;
    for (int i = total_registered_books; i < total_registered_books + total_of_books_to_register && counter < total_of_books_to_register; i++) {
        if (repeated_book == 1) {
            printf("!!! TENTE NOVAMENTE !!!\n");
        }
        printf("Titulo: ");
        scanf(" %49[^\n]", list_books[i].title);
        if (total_registered_books > 0) {
            repeated_book_index = check_repeated_book(list_books[i].title, list_books, total_registered_books);
            //
            if (repeated_book_index >= 0) {
                printf("===== PROBLEMA AO CADASTRAR LIVRO =====\n");
                printf("O livro '%s' ja esta cadastrado com %d exemplares\n", list_books[repeated_book_index].title, list_books[repeated_book_index].copies);
                repeated_book = 1;
                continue;
            } else {
                counter++;
            }
        }        

        printf("Codigo: ");
        scanf("%d", &list_books[i].code);

        printf("Autor: ");
        scanf(" %49[^\n]", list_books[i].author);

        printf("Ano de lancamento: ");
        scanf("%d", &list_books[i].year);

        printf("Total de exemplares: ");
        scanf("%d", &list_books[i].copies);

        fprintf(book_file, "%d;%s;%s;%d;%d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
    }
    //
    fclose(book_file);
    //
    if (counter == 0) {
        printf("Nenhum livro cadastrado\n");
    } else if (counter > 0) {
        printf("%d livro(s) cadastrado(s)\n", counter);
    }
}

int check_repeated_book(char input_title[], book list_books[], int total_registered_books) {
    for (int i = 0; i < total_registered_books; i++) {
        if (strcmp(input_title, list_books[i].title) == 0) {
            return i;
        }
    }
    return -1;
}

void show_books(book list_books[], int total_registered_books) {
    if (total_registered_books == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    for (int i = 0; i < total_registered_books; i++) {
        printf("%d; %s; %s; %d; %d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
    }
}

void search_book(book list_books[], int total_registered_books) {
    if (total_registered_books == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    int type_of_search_chosen;
    int code_to_search;
    int year_to_search;
    char title_to_search[50];
    char author_to_search[50];
    printf("===== SISTEMA DE BUSCA =====\n");
    printf("1. Buscar pelo codigo\n");
    printf("2. Buscar pelo titulo\n");
    printf("3. Buscar pelo autor\n");
    printf("4. Buscar pelo ano\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &type_of_search_chosen);
    if ((type_of_search_chosen >= 1) && (type_of_search_chosen <= 4)) {
        switch(type_of_search_chosen) {
            case 1:
            printf("Codigo para buscar: ");
            scanf("%d", &code_to_search);
            search_book_by_code(list_books, code_to_search, total_registered_books);
            break;

            case 2:
            printf("Titulo para buscar: ");
            scanf(" %49[^\n]", title_to_search);
            search_book_by_title(list_books, title_to_search, total_registered_books);
            break;

            case 3:
            printf("Autor para buscar: ");
            scanf(" %49[^\n]", author_to_search);
            search_book_by_author(list_books, author_to_search, total_registered_books);
            break;

            case 4:
            printf("Ano para buscar: ");
            scanf("%d", &year_to_search);
            search_book_by_year(list_books, year_to_search, total_registered_books);
            break;
        }
    } else {
        printf("A opcao '%d' nao existe!\n", type_of_search_chosen);
        return;
    }
}

void search_book_by_code(book list_books[], int code_to_search, int total_registered_books) {
    int book_found = 0;
    for (int i = 0; i < total_registered_books; i++) {
        if (list_books[i].code == code_to_search) {
            book_found = 1;
            printf("%d; %s; %s; %d; %d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
        }
    }
    if (book_found == 0) {
        printf("O livro com o codigo '%d' nao foi encontrado!\n", code_to_search);
    }
}

void search_book_by_title(book list_books[], char title_to_search[], int total_registered_books) {
    int book_found = 0;
    for (int i = 0; i < total_registered_books; i++) {
        if (strcmp(title_to_search, list_books[i].title) == 0) {
            book_found = 1;
            printf("%d; %s; %s; %d; %d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
        }
    }
    if (book_found == 0) {
        printf("O livro com o titulo '%s' nao foi encontrado!\n", title_to_search);
    }
}

void search_book_by_author(book list_books[], char author_to_search[], int total_registered_books) {
    int book_found = 0;
    for (int i = 0; i < total_registered_books; i++) {
        if (strcmp(author_to_search, list_books[i].author) == 0) {
            book_found = 1;
            printf("%d; %s; %s; %d; %d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
        }
    }
    if (book_found == 0) {
        printf("Nenhum livro do autor '%s' foi encontrado!\n", author_to_search);
    }
}

void search_book_by_year(book list_books[], int year_to_search, int total_registered_books) {
    int book_found = 0;
    for (int i = 0; i < total_registered_books; i++) {
        if (year_to_search == list_books[i].year) {
            book_found = 1;
            printf("%d; %s; %s; %d; %d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
        }
    }
    if (book_found == 0) {
        printf("Nenhum livro lancado em %d foi encontrado!\n", year_to_search);
    }
}

void edit_book(char file_name_books[], book list_books[], int total_registered_books) {
    if (total_registered_books == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    char title_of_the_book_to_edit[50];
    int chosen_edition_option;
    char new_title[50];
    char new_author[50];
    int new_year;
    int new_copies;
    FILE *book_file;
    book_file = fopen(file_name_books, "r");
    if (book_file == NULL) {
        return;
    }
    printf("Qual o titulo do livro que deseja editar: ");
    scanf(" %49[^\n]", title_of_the_book_to_edit);
    int found_book = 0;
    int found_book_index;
    for (int i = 0; i < total_registered_books && found_book == 0; i++) {
        if (strcmp(title_of_the_book_to_edit, list_books[i].title) == 0) {
            found_book_index = i;
            found_book = 1;
        }
    }
    if (found_book == 1) {
        printf("===== EDITAR O LIVRO '%s' =====\n", list_books[found_book_index].title);
        printf("1. Editar titulo\n");
        printf("2. Editar autor\n");
        printf("3. Editar ano\n");
        printf("4. Editar numero de exemplares\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &chosen_edition_option);
    } else {
        printf("O livro '%s' nao foi encontrado!\n", title_of_the_book_to_edit);
        return;
    }

    //
    if ((chosen_edition_option >= 1) && (chosen_edition_option <= 4)) {
        switch(chosen_edition_option) {
            case 1:
            printf("Novo titulo: ");
            scanf(" %49[^\n]", new_title);
            strcpy(list_books[found_book_index].title, new_title);
            break;

            case 2:
            printf("Novo autor: ");
            scanf(" %49[^\n]", new_author);
            strcpy(list_books[found_book_index].author, new_author);
            break;

            case 3:
            printf("Novo ano: ");
            scanf("%d", &new_year);
            list_books[found_book_index].year = new_year;
            break;

            case 4:
            printf("Novo numero de exemplares: ");
            scanf("%d", &new_copies);
            list_books[found_book_index].copies = new_copies;
            break;
        }
        fclose(book_file);
        book_file = fopen(file_name_books, "w");
        if (book_file == NULL) {
            return;
        }
        for (int i = 0; i < total_registered_books; i++) {
            fprintf(book_file, "%d;%s;%s;%d;%d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
        }
        fclose(book_file);
    } else {
        printf("A opcao '%d' nao existe!\n", chosen_edition_option);
    }
}

void delete_book(char file_name_books[], book list_books[], int total_registered_books) {
    if (total_registered_books == 0) {
        printf("Nao tem nenhum livro cadastrado ainda!\n");
        return;
    }
    FILE *book_file;
    FILE *temporary_file;
    char temporary_file_name[30] = "tempbooks.txt";
    char title_of_book_to_delete[50];
    int found_book = 0;
    int index_of_the_book_to_be_deleted = 0;
    book_file = fopen(file_name_books, "r");
    if (book_file == NULL) {
        return;
    }
    printf("Qual o titulo do livro que deseja excluir: ");
    scanf(" %49[^\n]", title_of_book_to_delete);
    for (int i = 0; i < total_registered_books && found_book != 1; i++) {
        if (strcmp(title_of_book_to_delete, list_books[i].title) == 0) {
            index_of_the_book_to_be_deleted = i;
            found_book = 1;
        }
    }
    if (found_book == 1) {
        temporary_file = fopen(temporary_file_name, "w");
        if (temporary_file == NULL) {
            return;
        }
        for (int i = 0; i < total_registered_books; i++) {
            if (i != index_of_the_book_to_be_deleted) {
                fprintf(temporary_file, "%d;%s;%s;%d;%d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
            }
        }
        fclose(book_file);
        fclose(temporary_file);
        
        book_file = fopen(file_name_books, "w");
        if (book_file == NULL) {
            return;
        }
        temporary_file = fopen(temporary_file_name, "r");
        if (temporary_file == NULL) {
            return;
        }

        int i = 0;
        while (fscanf(temporary_file, "%d;%49[^;];%49[^;];%d;%d\n", &list_books[i].code, list_books[i].title, list_books[i].author, &list_books[i].year, &list_books[i].copies) == 5) {
            if (list_books[i].code > index_of_the_book_to_be_deleted) {
                list_books[i].code = list_books[i].code - 1;
            }
            fprintf(book_file, "%d;%s;%s;%d;%d\n", list_books[i].code, list_books[i].title, list_books[i].author, list_books[i].year, list_books[i].copies);
            i++;
        }

        fclose(book_file);
        fclose(temporary_file);
        remove(temporary_file_name);
        printf("O livro '%s' foi excluido!\n", title_of_book_to_delete);

    } else {
        fclose(book_file);
        printf("O livro '%s' nao foi encontrado!\n", title_of_book_to_delete);
        return;
    }
}