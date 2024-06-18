#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Personal_data {
    char *surname;
    char *first_name;
    int age;
    long long int id;
    int sex;
    struct Personal_data *prev;
    struct Personal_data *next;

};
int option = -1;
int bool_num = -1;
char* filename_input;
struct Personal_data* newNode( char *surname, char *first_name,int age, long long id,int sex) {
    struct Personal_data *node = (struct Personal_data *) malloc(sizeof(struct Personal_data));
    node->age = age;
    node->sex = sex;
    node->first_name = (char*)malloc(strlen(first_name)+1);
    strcpy(node->first_name, first_name);
    node->surname = (char *)malloc(strlen(surname) + 1);
    strcpy(node->surname, surname);
    node->id = id;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
void add_person(struct Personal_data** head, int number_to_add, char *surname, char *first_name, int age, long long id, int sex) {
    for (int i = 0; i < number_to_add; i++) {
        struct Personal_data *new_node = newNode(surname, first_name, age, id, sex);
        if (*head == NULL) {
            *head = new_node;
            return;
        }
        (*head)->prev = new_node;
        new_node->next = *head;
        *head = new_node;
    }
}
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
//    switch (is_front){
//        case 0:{
////back
//        }break;
//        case 1:{
////front
//        }break;
//    }
}
    void display(struct Personal_data** head) {
        struct Personal_data *current = *head;
        while (current != NULL) {
            printf("Surname: %s\n", current->surname);
            printf("First Name: %s\n", current->first_name);
            printf("Age: %d\n", current->age);
            printf("ID: %lld\n", current->id);
            printf("Sex: %d\n", current->sex);
            printf("\n");
            current = current->next;
        }
    }


int load_data_from(struct Personal_data** head, char *filename) {
    FILE *fp;
}
int save_to_file(struct Personal_data** head, char *filename) {}
int sort_by_surname(struct Personal_data** head) {}

void free_list(struct Personal_data *head) {
    struct Personal_data *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->surname);
        free(temp->first_name);
        free(temp);
    }
}
void print_menu();
int main() {

    struct Lista* head;
    //head = (struct Lista*)malloc(sizeof(struct Lista));
    head = NULL;

    print_menu();


    while (option!=0){
        scanf_s("%d", &option);

        switch (option){
            case 0:
                return 0;

            case 1: {
                char *local_first_name;
                char *local_surname;
                int local_id = 0;
                int local_age = 0;
                int local_sex = -1;
                printf("How many people do you want to add to the list?");
                scanf_s("%d", &bool_num);
                printf("Input surname: ");
                int len_surname = 0;
                scanf_s("%n", &len_surname);
                char local_surname_input[len_surname + 1];
                scanf_s("%s", local_surname_input);
                local_surname = (char *)malloc(strlen(local_surname_input) + 1);
                strcpy(local_surname, local_surname_input);
                printf("Input first name: ");
                int len_first_name = 0;
                scanf_s("%n", &len_first_name);
                char local_first_name_input[len_first_name + 1];
                scanf_s("%s", local_first_name_input);
                local_first_name = (char *)malloc(strlen(local_first_name_input) + 1);
                strcpy(local_first_name, local_first_name_input);
                printf("Input age: ");
                scanf_s("%d", &local_age);
                printf("Input id: ");
                scanf_s("%lld", &local_id);
                printf("Input sex:\n 0 - male, 1 - female, 2 - other:");
                scanf_s("%d", &local_sex);
                add_person(&head, bool_num, local_surname, local_first_name, local_age, local_id, local_sex);
                print_menu();
                } break;

                case 2: {
                printf("0 - by surname, 1 - by name.");
                scanf_s("%d", &bool_num);
                search(&head, bool_num);

            }break;
            case 3: {
                delete_by_surname(&head);

            }break;
            case 4: {
//                printf("0 - from front, 1 - from back");
//                scanf_s("%d", &bool_num);
//                display_list(&head, bool_num);
                display(&head);

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
    free_list(head);
    return 0;
}
void print_menu(){
printf("0: Exit.\n");
printf("1: Adding any number of people to the list.\n");
printf("2: Searching for a person by surname or first name.\n");
printf("3: Deleting a selected person (by surname).\n");
printf("4: Displaying the list - from front / from back.\n");
printf("5: Reading the list from a file.\n");
printf("6: Saving the list to a file.\n");
printf("7: Sorting the list by surname.\n");
}
