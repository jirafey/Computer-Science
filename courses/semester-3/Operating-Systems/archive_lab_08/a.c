#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to run the child process logic
void runChildProcess(char *childArg, int *processedDigits, int *sum) {
    printf("pid (child): %d\n", getpid());

    // Build an array of strings for the new program and its arguments
    char *child_argv[] = {"./a", childArg, NULL};

    // Execute the new program within the child process
    execv("./a", child_argv);

    // If execv() fails, print an error message
    perror("execv");
    exit(1);
}

// Function to compute the sum of digits in a number
int sumOfDigits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

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

    // Arrays to keep track of processed digits
    int processedDigits[length];
    memset(processedDigits, 0, sizeof(processedDigits));

    // Variables to accumulate sums
    int sumFirstHalf = 0, sumSecondHalf = 0, totalSum = 0;

    // Process the first half
    for (size_t i = 0; i < upper_half; i++) {
        int digit = upper_half_str[i] - '0';
        if (!processedDigits[digit]) {
            processedDigits[digit] = 1;
            sumFirstHalf += digit;
        }
    }

    // Process the second half
    for (size_t i = 0; i < lower_half; i++) {
        int digit = lower_half_str[i] - '0';
        if (!processedDigits[digit]) {
            processedDigits[digit] = 1;
            sumSecondHalf += digit;
        }
    }

    // Print the sums for the first and second halves
    printf("Sum of first half: %d\n", sumFirstHalf);
    printf("Sum of second half: %d\n", sumSecondHalf);

    // Accumulate the sums
    totalSum += sumFirstHalf;
    totalSum += sumSecondHalf;

    // Print the total sum
    printf("Total sum: %d\n", totalSum);

    pid_t first_child_pid = fork();

    if (first_child_pid < 0) {
        perror("fork fail");
        exit(1);
    } else if (first_child_pid == 0) {  // First child process
        runChildProcess(upper_half_str, processedDigits, &totalSum);
    } else {  // Parent process
        pid_t second_child_pid = fork();

        if (second_child_pid < 0) {
            perror("fork fail");
            exit(1);
        } else if (second_child_pid == 0) {  // Second child process
            runChildProcess(lower_half_str, processedDigits, &totalSum);
        } else {  // Parent process
            int status_first_child, status_second_child;
            pid_t terminated_pid;

            // Wait for the first child to finish
            terminated_pid = waitpid(first_child_pid, &status_first_child, 0);
            if (terminated_pid == -1) {
                perror("waitpid for first child failed");
                exit(1);
            }

            // Print information for the first child
            printf("Parent pid: %d, Terminated Child pid: %d, Argument: %s, Exit Code: %d\n",
                   getpid(), terminated_pid, upper_half_str, WEXITSTATUS(status_first_child));

            // Wait for the second child to finish
            terminated_pid = waitpid(second_child_pid, &status_second_child, 0);
            if (terminated_pid == -1) {
                perror("waitpid for second child failed");
                exit(1);
            }

            // Print information for the second child
            printf("Parent pid: %d, Terminated Child pid: %d, Argument: %s, Exit Code: %d\n",
                   getpid(), terminated_pid, lower_half_str, WEXITSTATUS(status_second_child));

            // Calculate the final exit code for the parent
            int parentExitCode = WEXITSTATUS(status_first_child) + WEXITSTATUS(status_second_child);
            printf("Parent: Sum of exit codes: %d\n", parentExitCode);

            return parentExitCode;
        }
    }

    return 0;
}

