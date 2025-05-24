#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char first_name[30];
    char surname[30];
    int age;
    long long int id;
    int sex;
    struct person *next;
    struct person *previous;
};

struct person *first = NULL;

void add_person(char first_name[], char surname[], int age, int sex, long long int id) {
    struct person *new_person = (struct person*)malloc(sizeof(struct person));
    strcpy(new_person->first_name, first_name);
    strcpy(new_person->surname, surname);
    new_person->age = age;
    new_person->id = id;
    new_person->sex = sex;
    new_person->previous = NULL;
    new_person->next = first;
    if (first != NULL) {
        first->previous = new_person;
    }
    first = new_person;
}

void delete_person(char surname[]) {
    struct person *current = first;
    struct person *previous = NULL;
    if (current != NULL && strcmp(current->surname, surname) == 0) {
        first = current->next;
        if (first != NULL) {
            first->previous = NULL;
        }
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->surname, surname) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Person not found\n");
        return;
    }
    previous->next = current->next;
    if (current->next != NULL) {
        current->next->previous = previous;
    }
    free(current);
}


void display_people(int display_direction) {
    if (first == NULL) {
        printf("Error: linked list is empty.\n");
        return;
    }

    struct person *current = first;
    if(display_direction == 1) {
        while (current != NULL) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            current = current->next;
        }
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        while (current != NULL) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            current = current->previous;
        }
    }
}

void search_person(char search_value[], int search_by) {
    struct person *current = first;
    while (current != NULL) {
        if (search_by == 1 && strcmp(current->first_name, search_value) == 0) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            return;
        }
        else if (search_by == 2 && strcmp(current->surname, search_value) == 0) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            return;
        }
        current = current->next;
    }
    printf("Person not found\n");
}


void read_people_from_file() {
    char filename[100];
    printf("Enter the name of the file: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (!feof(file)) {
        char first_name[100];
        char surname[100];
        int age;
        int sex;
        long long int id;
        fscanf(file, "%s %s %d %d %lld\n", first_name, surname, &age, &sex, &id);
        add_person(first_name, surname, age, sex, id);
    }

    fclose(file);
}

void save_people_to_file() {
    FILE *file;
    file = fopen("people.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    struct person *current = first;
    while (current != NULL) {
        fprintf(file, "%s\n%s\n%d\n%d\n%lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
        current = current->next;
    }
    fclose(file);
    printf("People list saved to file successfully.\n");
}
void sort_people_by_surname() {
    struct person *current1 = first;
    while (current1 != NULL) {
        struct person *current2 = current1->next;
        while (current2 != NULL) {
            if (strcmp(current1->surname, current2->surname) > 0) {
                char temp_first_name[100];
                char temp_surname[100];
                strcpy(temp_first_name, current1->first_name);
                strcpy(temp_surname, current1->surname);
                strcpy(current1->first_name, current2->first_name);
                strcpy(current1->surname, current2->surname);
                strcpy(current2->first_name, temp_first_name);
                strcpy(current2->surname, temp_surname);
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    struct person *current = first;
    while (current != NULL) {
        printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
        current = current->next;
    }
}



int main() {
    int choice;
    char first_name[30];
    char surname[30];
    int add_count;
    int display_direction;
    char search_term[30];
    while(1) {
        printf("Enter 0 to quit\n");
        printf("Enter 1 to add a person\n");
        printf("Enter 2 to display people\n");
        printf("Enter 3 to search for a person\n");
        printf("Enter 4 to delete a person\n");
        printf("Enter 5 to read from file\n");
        printf("Enter 6 to save from file\n");
        printf("Enter 7 to sort by surname\n");
        scanf_s("%d", &choice);
        switch(choice) {
            case 0:
                return -1;
            case 1:
                printf("Enter first name: ");
                scanf_s("%s", first_name);
                printf("Enter surname: ");
                scanf_s("%s", surname);
                int age, sex, id;
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter sex (1 for male, 2 for female): ");
                scanf("%d", &sex);
                printf("Enter id: ");
                scanf("%lld", &id);
                printf("Enter number of times to add: ");
                scanf_s("%d", &add_count);
                for(int i = 0; i < add_count; i++) {

                    add_person(first_name, surname, age, sex, id);
                }

                break;
            case 2:
                printf("Enter 1 to display from front or 2 to display from back: ");
                if (scanf_s("%d", &display_direction) != 1) {
                    printf("Invalid input\n");
                    continue;
                }
                if (display_direction != 1 && display_direction != 2) {
                    printf("Invalid input\n");
                    continue;
                }
                display_people(display_direction);
                break;

            case 3:


                printf("Enter 1 to search by first name or 2 to search by surname: ");
                char search_term[30];
                int search_by;
                scanf_s("%d", &search_by);
                printf("Enter search term: ");
                scanf_s("%s", search_term);
                search_person(search_term, search_by);
                break;

            case 4:
                printf("Enter surname of person to delete: ");
                scanf_s("%s", surname);
                delete_person(surname);
                break;
            case 5:
                read_people_from_file();
                break;
            case 6:
                save_people_to_file();
                break;
            case 7:
                sort_people_by_surname();
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}
