#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::endl;



int main1(int WIDTH)
{
    int *vector_of_pointers = new int[WIDTH];

    cout << "vector_of_pointers addresses:" << endl;
    for(int i = 0; i < WIDTH; ++i) {
        cout << &vector_of_pointers[i] << endl;
    }
    cout << endl;

    delete [] vector_of_pointers;
    return EXIT_SUCCESS;
}

int main(){
    main1(3);
}