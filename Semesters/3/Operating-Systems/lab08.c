#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void runChildProcess(char *childArg, char *processType) {
    printf("%s pid: %d, ppid: %d: %s\n", processType, getpid(), getppid(), childArg);
    
    char *child_argv[] = {"./lab08", childArg, NULL};
    execv("./lab08", child_argv);
    
    perror("execv");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return 1;
    }

    char *input = argv[1];
    size_t length = strlen(input);

    if (length < 1 || length > 25) {
        fprintf(stderr, "Error: Argument length out of range\n");
        return 1;
    }

    for (size_t i = 0; i < length; i++) {
        if (!isdigit(input[i])) {
            fprintf(stderr, "Error: Argument is not a number\n");
            return 1;
        }
    }

    if (length == 1) {
        int digit = atoi(input);
        printf("Parent: %d: exit code: %d\n", getpid(), digit);
        return digit;
    }

    size_t upper_half = length / 2;
    size_t lower_half = length - upper_half;

    char upper_half_str[upper_half + 1];
    char lower_half_str[lower_half + 1];

    strncpy(upper_half_str, input, upper_half);
    upper_half_str[upper_half] = '\0';

    strncpy(lower_half_str, input + upper_half, lower_half);
    lower_half_str[lower_half] = '\0';

    printf("Parent: %d: '%s' '%s' '%s'\n", getpid(), input, upper_half_str, lower_half_str);

    pid_t first_child_pid = fork();

    if (first_child_pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (first_child_pid == 0) {
        runChildProcess(upper_half_str, "1st child");
    } else {
        pid_t second_child_pid = fork();

        if (second_child_pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (second_child_pid == 0) {
            runChildProcess(lower_half_str, "2nd child");
        } else {
            int status_first_child, status_second_child;
            pid_t terminated_pid;

            terminated_pid = waitpid(first_child_pid, &status_first_child, 0);
            if (terminated_pid == -1) {
                perror("waitpid for 1st child failed");
                exit(1);
            }

            printf("Parent: %d: 1st child : %d exit code %d\n\n", getpid(), terminated_pid, WEXITSTATUS(status_first_child));

            terminated_pid = waitpid(second_child_pid, &status_second_child, 0);
            if (terminated_pid == -1) {
                perror("waitpid for 2nd child failed");
                exit(1);
            }

            printf("Parent: %d: 2nd child : %d exit code %d\n", getpid(), terminated_pid, WEXITSTATUS(status_second_child));

            int parentExitCode = WEXITSTATUS(status_first_child) + WEXITSTATUS(status_second_child);
            printf("Parent: %d: Sum of exit codes from children: %d\n", getpid(), parentExitCode);

            return parentExitCode;
        }
    }

    return 0;
}

