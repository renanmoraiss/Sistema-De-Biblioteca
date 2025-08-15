#include <stdio.h>
#include "library.h"
#include "menu.h"

int main() {
    book list_books[MAX_BOOKS];
    int total_books;
    int chosen_menu_option;
    char file_name_books[30] = "books.txt";

    total_books = load_books(file_name_books, list_books);

    do {
        chosen_menu_option = menu();
        switch(chosen_menu_option) {
            case 1:
            register_book(file_name_books, list_books, total_books);
            total_books = load_books(file_name_books, list_books);
            break;
            
            case 2:
            show_books(list_books, total_books);
            break;
            
            case 3:
            search_book(list_books, total_books);
            break;
            
            case 4:
            edit_book(file_name_books, list_books, total_books);
            break;
            
            case 5:
            delete_book(file_name_books, list_books, total_books);
            total_books = load_books(file_name_books, list_books);
            break;
            
            case 6:
            close_system();
            break;
        }
    } while(chosen_menu_option != 6);

    return 0;
}