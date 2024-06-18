

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "No argument passed\n");
        return 1;
    }

    char *input = argv[1];
    size_t length = strlen(input);

    if (length == 1) {
        int digit = atoi(input);
        printf("Returned value: %d\n", digit);
        return digit;
    } else if (length >= 26) {
        fprintf(stderr, "Argument is longer than 25 characters\n");
        return 1;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isdigit(input[i])) {
            fprintf(stderr, "Argument is not a number\n");
            return 1;
        }
    }

    size_t upper_half = length / 2;
    size_t lower_half = length - upper_half;

    char upper_half_str[upper_half + 1];
    char lower_half_str[lower_half + 1];

    strncpy(upper_half_str, input, upper_half);
    upper_half_str[upper_half] = '\0';

    strncpy(lower_half_str, input + upper_half, lower_half);
    lower_half_str[lower_half] = '\0';

    printf("Upper half: %s\n", upper_half_str);
    printf("Lower half: %s\n", lower_half_str);

    pid_t first_child_pid = fork();

    if (first_child_pid < 0) {
        perror("fork fail");
        exit(1);
    } else if (first_child_pid == 0) {
        printf("pid (first child): %d\n", getpid());

        char *first_child_argv[] = {"./l", upper_half_str, NULL};

        execv("./l", first_child_argv);

        perror("execv");
        exit(1);
    } else {
        wait(NULL); 

        pid_t second_child_pid = fork();

        if (second_child_pid < 0) {
            perror("fork fail");
            exit(1);
        } else if (second_child_pid == 0) {
            printf("pid (second child): %d\n", getpid());

            char *second_child_argv[] = {"./l", lower_half_str, NULL};

            execv("./l", second_child_argv);

            perror("execv");
            exit(1);
        } else {  
            wait(NULL);  
        }
    }

    return 0;
}

