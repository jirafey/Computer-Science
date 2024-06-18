#include <stdio.h>
void zad1(int * array_given, int size){
    // *array_given = array_given[0]

    printf("%d\n", size);
    for (int i=0; i<size; i++){   
        printf("YO");
        array_given[i]  = 0;
        printf("%d\n",array_given[i]);
    }
    for (int j; j<size; j++){
        array_given[j] = j;
        printf("%d\n", array_given[j]);
    }

}

int main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9};
    zad1(arr, 10);
}
