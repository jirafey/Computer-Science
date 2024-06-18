#include <stdio.h>
#include <stdlib.h>

struct Test{
    int number;
    int * pointer;
};

int *ex_1(int n){
    int *block = (int*)malloc(n* sizeof(int));
    for(int i=0; i<n; i++)
        block[i]=i;
    return block;
}


int ex_2(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file");
        return 1;
    }
    int num_counter = 0;
    int x;
    while (fscanf(fp, "%d", &x) == 1) {
        if(x==100)
            num_counter++;
    }
    fclose(fp);
    return num_counter;
}

void ex_3(struct Test *array, const int size){

    for (int i = 0; i < size; i++) {
        array[i].pointer= (int* )malloc(sizeof(int));
        *(array[i].pointer) = 100;
    }
    for (int i = 0; i < size; i++) {
        free(array[i].pointer);
    }
}

int main() {
    int* block = ex_1(10);
    for(int i=0; i<10; i++)
        printf("%d ", block[i]);
    free(block);
    printf("\n");
    printf("%d\n", ex_2("100.txt"));

    int test_size = 100;
    struct Test *array = (struct Test *)malloc(test_size * sizeof(struct Test));
    ex_3(array, test_size);
    free(array);
    return 0;
}
