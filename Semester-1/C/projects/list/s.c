#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SearchType {
    int type;
};

struct Person {
    char *first_name;
    char *surname;
    int age;
    long long int id;
    int sex;
    struct Person *next;
    struct Person *previous;
};

struct Person *first = NULL;

void addPerson(char *first_name, char *surname, int age, int sex, long long int id) {
    struct Person *newPerson = (struct Person*) malloc(sizeof(struct Person));
    newPerson->first_name = strdup(first_name);
    newPerson->surname = strdup(surname);
    newPerson->age = age;
    newPerson->id = id;
    newPerson->sex = sex;
    newPerson->previous = NULL;
    newPerson->next = first;
    if (first != NULL) {
        first->previous = newPerson;
    }
    first = newPerson;
}

void deletePerson(char *surname) {
    struct Person *current = first;
    struct Person *previous = NULL;
    if (current != NULL && strcmp(current->surname, surname) == 0) {
        first = current->next;
        if (first != NULL) {
            first->previous = NULL;
        }
        free(current->first_name);
        free(current->surname);
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
    free(current->first_name);
    free(current->surname);
    free(current);
}

void displayPeople(int display_direction) {
    if (first == NULL) {
        printf("Error: linked list is empty.\n");
        return;
    }

    struct Person *current = first;
    if (display_direction == 1) {
        while (current != NULL) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            current = current->next;
        }
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        while (current != NULL) {
            printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex, current->id);
            current = current->previous;
        }
    }
}

void searchPerson(char *search_string, struct SearchType search_type) {
    struct Person *current = first;
    if (current == NULL) {
        printf("Error: linked list is empty.\n");
        return;
    }
    if (search_type.type == 1) {
        while (current != NULL) {
            if (strcmp(current->surname, search_string) == 0) {
                printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex,
                       current->id);
                return;
            }
            current = current->next;
        }
    } else if (search_type.type == 2) {
        while (current != NULL) {
            if (strcmp(current->first_name, search_string) == 0) {
                printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex,
                       current->id);
                return;
            }
            current = current->next;
        }
    } else if (search_type.type == 3) {
        int age = atoi(search_string);
        while (current != NULL) {
            if (current->age == age) {
                printf("%s %s %d %d %lld\n", current->first_name, current->surname, current->age, current->sex,
                       current->id);
                return;
            }
            current = current->next;
        }
    } else {
        printf("Invalid search type\n");
    }
    printf("Person not found\n");
}