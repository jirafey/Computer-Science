#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// typedefs
typedef struct Personal_data{
    char *name;
    char *surname;
    long long int id;
    int sex;
    int age; // Also could implement get_age() from id
    struct Personal_data *previous;
    struct Personal_data *next;
} Person;


// function prototypes
Person *newNode(char *name, char *surname, int age, long long int id, int sex);
void print_menu();
void add_personal_data(Person **head);
//void search_by_surname();
//void delete_personal_data();
void display_list(Person *head);
//void load_from_file(Person **head);
//void save_to_file(Person **head);
//void sort();


int main(int argc, char *argv[]){
    int option = -1;
    int is_name;
    Person *head = NULL;
    while (option!=0){
        print_menu();
        scanf_s("%d", &option);

        switch (option) {
            case 0:
            return 1;

            case 1: {

                add_personal_data(&head);
            }
                break;

            case 2:
                printf("0 - by surname, 1 - by name. ");
                scanf_s("%d", &is_name);
//                search_by_surname();
                break;
//
//            case 3:
////                delete_personal_data();
//                break;

            case 4:
                display_list(head);
                break;

//            case 5:
////                load_from_file();
//                break;
//
//            case 6:
////                save_to_file();
//                break;
//
//            case 7:
////                sort();
//                break;
        }
    }
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

void add_personal_data(Person **head){
    int number_of_records;
    char *name = NULL;
    char *surname = NULL;
    int age;
    long long int id;
    int sex;
    int name_len, surname_len;

    printf("How many records do you want to add?");
    scanf("%d", &number_of_records);

    for (int i = 0; i < number_of_records; i++){
        printf("Enter the name:");
        name_len = scanf("%ms", &name);
        printf("Enter the surname:");
        surname_len = scanf("%ms", &surname);
        printf("Enter the age:");
        scanf("%d", &age);
        printf("Enter the ID:");
        scanf("%lld", &id);
        printf("Enter the sex (0 = male, 1 = female, 2 = other):");
        scanf("%d", &sex);
        printf("%s, %s, %d, %lld, %d", name,surname,age,id,sex);
        Person *node = newNode(name, surname, age, id, sex);

        // Clean up since we don't need those values anymore
        free(name);
        name = NULL;
        free(surname);
        surname = NULL;
    }
}


void display_list(Person *head) {

    int choice;
    printf("Do you want to display the list from oldest(0) to latest or from latest to oldest (1)?");
    scanf_s("%d", &choice);
    if (choice == 1) {
        // Display the list from the oldest to the latest
        Person *current = head;
        printf("Number 1:%s, %s, %d, %lld, %d", head->name,head->surname,head->age,head->id,head->sex);
        while (current != NULL) {
            printf("Name: %s, Surname: %s, Age: %d, ID: %lld, Sex: %d", current->name, current->surname, current->age,
                   current->id, current->sex);
            current = current->next;
        }
    } else {
        // Display the list from the latest to the oldest
        Person *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        while (current != NULL) {
            printf("Name: %s, Surname: %s, Age: %d, ID: %lld, Sex: %d", current->name, current->surname, current->age,
                   current->id, current->sex);
            current = current->previous;
        }
    }
}


Person *newNode(char *name, char *surname, int age, long long int id, int sex){
    Person *node = (Person *)malloc(sizeof(Person));
    node -> age = age;
    node -> id = id;
    node -> sex = sex;
    node -> name = (char *)malloc(strlen(name)+1);
    // strcpy() is necessary because malloc allocates memory on the heap,
    // but does not initialize it, so we need to copy the relevant data into that memory.
    strcpy(node->name, name);
    node -> surname = (char *)malloc(strlen(surname)+1);
    strcpy(node->surname, surname);
    return node;
}
