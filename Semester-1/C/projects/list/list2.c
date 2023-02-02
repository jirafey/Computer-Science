#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

struct Lista {
    int wiek;
    long long int pesel;
    char imie[50];
    char nazwisko[50];
    char plec[2];
    struct Lista* previous;
    struct Lista* next;
};


void show(struct Lista* head);
void show_reverse(struct Lista* head);
int list_size(struct Lista* head);
void push_front(struct Lista** head, int w, long long int p, char i[50], char n[50], char pl[2]);
void pop_front(struct Lista** head);

void zapis(struct Lista* head, int option);
void wczytywanie(struct Lista** head, int option);
void wyszukiwarka(struct Lista*, char wyszukiwanie[50], int option);

int main() {
    struct Lista *head;
    //head = (struct Lista*)malloc(sizeof(struct Lista));
    head = NULL;


    int option = -1;
    int number = -1;
    int index = -1;

    while (1) {
        int w;
        long long int p;
        char i[50];
        char n[50];
        char pl[2];
        char wyszukiwanie[50];
        system("cls");
        printf("\nAktualny stan listy: %d", list_size(head));
        show(head);

        printf("\n\nCo chcesz zrobic?\n");
        printf("1. Dodac osobe.\n");
        printf("2. Usunac osobe.\n");
        printf("3. Wyswietlic liste w odwrotnej kolejnosci.\n");
        printf("4. Wyszukiwarka\n");
        printf("5. Wyswietlic opcje zapisu/wczytywania.\n");
        printf("0. Zakonczyc program.\n");


        scanf_s("%d", &option);

        switch (option) {
            case 0: {
                return 0;

            }
                break;
            case 1: {
                printf("\nGdzie chcesz dodac osobe?\n");
                printf("1. Dodac osobe na poczatek listy.\n");
                printf("2. Dodac osobe na koniec listy.\n");
                printf("3. Dodac osobe na wybrana pozycje.\n");
                scanf_s("%d", &option);


            }
                break;
            default: {
                printf("Podaj wlasciwa opcje.");
                Sleep(2000);
            }
                break;
        }


        return 0;
    }
}
void push_front(struct Lista** head, int w, long long int p, char i[50], char n[50], char pl[2])
{
    if (*head == NULL) {
        *head = (struct Lista*)malloc(sizeof(struct Lista));
        (*head)->wiek = w;
        (*head)->pesel = p;
        strcpy((*head)->imie, i);
        strcpy((*head)->nazwisko, n);
        strcpy((*head)->plec, pl);
        (*head)->previous = NULL;
        (*head)->next = NULL;
    }
    else {
        struct Lista* current;
        current = (struct Lista*)malloc(sizeof(struct Lista));
        current->wiek = w;
        current->pesel = p;
        strcpy(current->imie, i);
        strcpy(current->nazwisko, n);
        strcpy(current->plec, pl);
        current->previous = NULL;
        current->next = (*head);
        (*head)->previous = current;
        *head = current;
    }

}

void push_back(struct Lista** head,int w, long long int p, char i[50], char n[50], char pl[2])
{

    if (*head == NULL)
    {
        *head = (struct Lista*)malloc(sizeof(struct Lista));
        (*head)->wiek = w;
        (*head)->pesel = p;
        strcpy((*head)->imie, i);
        strcpy((*head)->nazwisko, n);
        strcpy((*head)->plec, pl);
        (*head)->previous = NULL;
        (*head)->next = NULL;
    }
    else
    {
        struct Lista* current = *head;
        // struct Lista* new_element; ?????????

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (struct Lista*)malloc(sizeof(struct Lista));
        current->next->wiek = w;
        strcpy(current->next->imie, i);
        strcpy(current->next->nazwisko, n);
        current->next->pesel = p;
        strcpy(current->next->plec, pl);
        current->next->previous = current;
        current->next->next = NULL;
    }



}

void push_by_index(struct Lista** head, int position, int w, long long int p, char imie[50], char n[50], char pl[2])
{
    position--;
    if (position == 0) push_front(head, w, p, imie, n, pl);
    else
    {
        if (position == list_size(*head)) push_back(head, w ,p, imie, n, pl);
        else
        {
            struct Lista* current = *head;
            struct Lista* tmp;

            int i = 0;
            while (current->next != NULL && i < position - 1) {
                current = current->next;
                i++;
            }
            tmp = current->next;
            current->next = (struct Lista*)malloc(sizeof(struct Lista));
            current->next->wiek = w;
            current->next->pesel = p;
            strcpy(current->next->imie, imie);
            strcpy(current->next->nazwisko, n);
            strcpy(current->next->plec, pl);
            current->next->previous = current;
            tmp->previous = current->next;
            current->next->next = tmp;

        }
    }


}

void pop_front(struct Lista** head)
{

    if (*head != NULL) {
        if ((*head)->next == NULL) {
            *head = NULL;
        }
        else {
            struct Lista* tmp;
            tmp = (*head)->next;
            free(*head);
            *head = tmp;
            (*head)->previous = NULL;
        }

    }

}

void pop_back(struct Lista** head)
{

    if ((*head)->next == NULL)
    {
        *head = NULL;
    }
    else
    {
        struct Lista* current = *head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}


void pop_by_index(struct Lista** head, int position)
{
    position--;
    if (position == 0) {
        pop_front(head);
    }
    else if (position == (list_size(*head) - 1)) {
        pop_back(head);
    }
    else
    {
        struct Lista* current = *head;
        struct Lista* tmp;

        int i = 0;
        while (current->next != NULL && i < position - 1) {
            current = current->next;
            i++;
        }

        tmp = current->next;
        current->next = tmp->next;
        current->next->previous = current;
        free(tmp);
    }


}

void show(struct Lista* head)
{
    int licznik = 1;
    printf("\n");
    if (head == NULL) printf("List is empty");
    else
    {
        struct Lista* current = head;
        do {
            printf("%d. Wiek: %d PESEL: %lld Imie: %s Nazwisko: %s Plec: %s", licznik, current->wiek, current->pesel, current->imie, current->nazwisko, current->plec);
            printf("\n");
            current = current->next;
            licznik++;
        } while (current != NULL);
    }
}

void show_reverse(struct Lista* head)
{
    printf("\n");
    if (head == NULL) {
        printf("List is empty");
    }
    else
    {
        struct Lista* current = head;
        while (current->next != NULL) {
            current = current->next; //idziemy na koniec listy
        }


        do {
            printf("Wiek: %d PESEL: %lld Imie: %s Nazwisko: %s Plec: %s", current->wiek, current->pesel, current->imie, current->nazwisko, current->plec);
            printf("\n");
            current = current->previous;
        } while (current != NULL);

    }
}

int list_size(struct Lista* head)
{
    int counter = 0;
    if (head == NULL) return counter;
    else
    {
        struct Lista* current = head;
        do {
            counter++;
            current = current->next;
        } while (current != NULL);
    }
    return counter;
}

void zapis(struct Lista* head,int option) {
    FILE* p;
    if (head == NULL) {
        printf("Brak danych do zapisu!");
    }else{
        if (option == 1) {
            fopen_s(&p, "lista.txt", "w");
        }
        else {
            fopen_s(&p, "lista.txt", "a");
        }
        struct Lista* current = head;
        do {
            fprintf_s(p, "%d %lld %s %s %s %s", current->wiek, current->pesel, current->imie, current->nazwisko,current->plec, "\n");
            current = current->next;
        } while (current!=NULL);
        printf("Pomyslnie zapisano dane!");

        fclose(p);
    }
    Sleep(2000);
}

void wczytywanie(struct Lista** head, int option) {
    FILE* plik;
    int w;
    long long int p;
    char i[50];
    char n[50];
    char pl[2];
    fopen_s(&plik, "lista.txt", "r");
    while (!feof(plik)) {
        fscanf_s(plik, "%d %lld %49s %49s %1s", &w, &p, &i,50, &n,50, pl,2);
        push_back(head, w, p, i,n, pl);
    }
    pop_back(head);
    fclose(plik);

}

void show_index(struct Lista* head, int index) {
    int licznik = 1;
    printf("\n");

    struct Lista* current = head;
    while (index > 0) {
        current = current->next;
        index--;
    }
    printf("Wiek: %d PESEL: %lld Imie: %s Nazwisko: %s Plec: %s", current->wiek, current->pesel, current->imie, current->nazwisko, current->plec);
    printf("\n");
    licznik++;
}
