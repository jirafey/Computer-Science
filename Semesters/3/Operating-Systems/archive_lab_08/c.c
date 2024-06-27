#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_child(char *arg) {
    printf("%d %d %s %d\n", getpid(), getppid(), arg, atoi(arg));
    exit(atoi(arg));
}

int main(int argc, char *argv[]) {
    // Sprawdzenie liczby argumentów
    if (argc != 2 || strlen(argv[1]) > 25) {
        fprintf(stderr, "Błąd: Nieprawidłowa liczba argumentów lub argument spoza zakresu.\n");
        exit(1);
    }

    // Jeżeli argument ma długość 1, zwróć wartość cyfry
    if (strlen(argv[1]) == 1) {
        printf("%d\n", atoi(argv[1]));
        exit(atoi(argv[1]));
    }

    // Oblicz środek łańcucha
    int length = strlen(argv[1]);
    int middle = length / 2;

    // Utwórz dwie "połówki" łańcucha
    char first_half[middle + 1];
    char second_half[length - middle + 1];

    strncpy(first_half, argv[1], middle);
    first_half[middle] = '\0';

    strcpy(second_half, argv[1] + middle);

    // Fork i wykonanie dzieci
    pid_t child1, child2;
    if ((child1 = fork()) == 0) {
        // Dziecko 1
        execute_child(first_half);
    } else if ((child2 = fork()) == 0) {
        // Dziecko 2
        execute_child(second_half);
    } else {
        // Rodzic
        int status1, status2;
        waitpid(child1, &status1, 0);
        waitpid(child2, &status2, 0);

        // Wypisz informacje o dzieciach
        printf("%d %d %s %d\n", getpid(), child1, first_half, WEXITSTATUS(status1));
        printf("%d %d %s %d\n", getpid(), child2, second_half, WEXITSTATUS(status2));

        // Zakończ program z sumą kodów powrotu dzieci
        exit(WEXITSTATUS(status1) + WEXITSTATUS(status2));
    }

    return 0;
}

