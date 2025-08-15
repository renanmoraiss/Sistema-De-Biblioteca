#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100

struct Book {
    int code;
    char title[50];
    char author[50];
    int year;
    int copies;
};

typedef struct Book book;

int load_books(char file_name_books[], book list_books[]);
void register_book(char file_name_books[], book list_books[], int total_registered_books);
int check_repeated_book(char input_title[], book list_books[], int total_registered_books);
void show_books(book list_books[], int total_registered_books);
void search_book(book list_books[], int total_registered_books);
void search_book_by_code(book list_books[], int code_to_search, int total_registered_books);
void search_book_by_title(book list_books[], char title_to_search[], int total_registered_books);
void search_book_by_author(book list_books[], char author_to_search[], int total_registered_books);
void search_book_by_year(book list_books[], int year_to_search, int total_registered_books);
void edit_book(char file_name_books[], book list_books[], int total_registered_books);
void delete_book(char file_name_books[], book list_books[], int total_registered_books);

#endif