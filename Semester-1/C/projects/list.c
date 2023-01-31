
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Personal_data {
    char surname[1024];
    char first_name[1024];
    int age;
    long long int id;
    int sex;
    struct Personal_data *prev;
    struct Personal_data *next;

};
int option = -1;
int bool_num = -1;
char* filename_input;
int add_person(struct Personal_data** head, int number_to_add) {}
int search(struct Personal_data** head, int is_first_name) {
    switch (is_first_name){
        case 0:{
//surname
        }break;
        case 1:{
//first_name
        }break;
    }
}

int delete_by_surname(struct Personal_data** head) {}
int display_list(struct Personal_data** head, int is_front) {
    switch (is_front){
        case 0:{
//back
        }break;
        case 1:{
//front
        }break;
    }
}
int load_data_from(struct Personal_data** head, char *filename) {
    FILE *fp;
}
int save_to_file(struct Personal_data** head, char *filename) {}
int sort_by_surname(struct Personal_data** head) {}


int main() {

    struct Lista* head;
    //head = (struct Lista*)malloc(sizeof(struct Lista));
    head = NULL;

    printf("Exit.");
    printf("1: Adding any number of people to the list.");
    printf("2: Searching for a person by surname or first name.");
    printf("3: Deleting a selected person (by surname).");
    printf("4: Displaying the list - from front / from back.");
    printf("5: Reading the list from a file.");
    printf("6: Saving the list to a file.");
    printf("7: Sorting the list by surname.");


    while (option!=0){
        scanf_s("%d", &option);

        switch (option){
            case 0: {
                return 0;

            }break;
            case 1: {
                printf("How many people do you want to add to the list?");
                scanf_s("%d", &bool_num);
                add_person(&head,bool_num);

            }break;
            case 2: {
                printf("0 - by surname, 1 - by name.");
                scanf_s("%d", &bool_num);
                search(&head, bool_num);

            }break;
            case 3: {
                delete_by_surname(&head);

            }break;
            case 4: {
                printf("0 - from front, 1 - from back");
                scanf_s("%d", &bool_num);
                display_list(&head, bool_num);

            }break;
            case 5: {
                printf("Input the name of the file you want to load data from");
                scanf_s("%d", &filename_input);
                load_data_from(&head,filename_input);

            }break;
            case 6: {
                printf("Input the name of the file you want to save data to");
                scanf_s("%d", &filename_input);
                save_to_file(&head, filename_input);

            }break;
            case 7: {
                sort_by_surname(&head);

            }break;
            default: {
                printf("Please input a proper option.");
            }
        }
    }
    return 0;
}
