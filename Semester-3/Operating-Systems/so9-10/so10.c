#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_LICZBY 1000000
#define MAX_WATKI 100

double sekwencja[MAX_LICZBY];
double suma = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

double oblicz_pi(int n) {
    double temp = 0.0;
    double result = 3.0;

    for (int i = 0; i < n; i++) {
        double base = i * 2 + 2;
        temp = 4.0 / (base * (base + 1) * (base + 2));

        result += (i % 2 == 0) ? temp : -temp;
    }

    return result;
}

double result = 3.0;

typedef struct {
    int from;
    int size;
} ThreadData;

// Function to calculate the elapsed time
void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td) {
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0) {
        td->tv_nsec += 1000000000;
        td->tv_sec--;
    } else if (td->tv_sec < 0 && td->tv_nsec > 0) {
        td->tv_nsec -= 1000000000;
        td->tv_sec++;
    }
}

void *threadFunction(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int from = data->from;
    int size = data->size;
    pthread_t tid = pthread_self();

    printf("Thread %lx size=%d first==%d\n", tid, size, from);

    double threadResult = 0;
    double temp = 0.0;

    for (int i = from; i < from + size; i++) {
        double o = i * 2 + 2;
        temp = 4.0 / (o * (o + 1) * (o + 2));

        if (i % 2 == 0) {
            threadResult += temp;
        } else {
            threadResult -= temp;
        }
    }

    pthread_mutex_lock(&mutex);
    result += threadResult;
    pthread_mutex_unlock(&mutex);

    printf("Thread %lx sum=%.20f\n", tid, threadResult);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <liczba wyrazow ciagu> <liczba watkow>\n", argv[0]);
        return 1;
    }

    int liczba = atoi(argv[1]);
    int watki = atoi(argv[2]);

    if (liczba <= 1 || liczba >= MAX_LICZBY) {
        printf("Invalid value for liczba\n");
        return 1;
    }

    if (watki <= 1 || watki >= min(MAX_WATKI, liczba)) {
        printf("Invalid value for watki\n");
        return 1;
    }

    pthread_t threads[watki];
    int numberForThreads = liczba / watki;
    int remainder = liczba % watki;

    ThreadData data[watki];

    struct timespec start, finish, delta;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (remainder != 0) {
        for (int i = 0; i < watki - 1; i++) {
            data[i].from = i * numberForThreads;
            data[i].size = numberForThreads;

            pthread_create(&threads[i], NULL, threadFunction, (void *)&data[i]);
        }

        data[watki - 1].from = (watki - 1) * numberForThreads;
        data[watki - 1].size = numberForThreads + remainder;

        pthread_create(&threads[watki - 1], NULL, threadFunction, (void *)&data[watki - 1]);
    } else {
        for (int i = 0; i < watki; i++) {
            data[i].from = i * numberForThreads;
            data[i].size = numberForThreads;

            pthread_create(&threads[i], NULL, threadFunction, (void *)&data[i]);
        }
    }

    // Join threads before printing the result
    for (int i = 0; i < watki; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    sub_timespec(start, finish, &delta);

    // Convert to seconds
    double seconds = (double)delta.tv_sec + (double)delta.tv_nsec / 1e9;

    // Print the result in nanoseconds
    printf("\nw/Threads  PI=%.20f time=%f nanoseconds\n", result, seconds);

    clock_gettime(CLOCK_MONOTONIC, &start);
    double iterativeResult = oblicz_pi(liczba);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    sub_timespec(start, finish, &delta);

    // Convert to seconds
    seconds = (double)delta.tv_sec + (double)delta.tv_nsec / 1e9;

    // Print the result in nanoseconds
    printf("wo/Threads PI=%.20f time=%f nanoseconds\n\n", iterativeResult, seconds);

    return 0;
}

