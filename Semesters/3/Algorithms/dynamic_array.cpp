#include <iostream>
#include "dynamic_array.h"
using namespace std;

class some_object {
public:

    some_object(int value) {
        data = value;
    }

    int getData() const {
        return data;
    }

private:
    int data;
};

int main()
{
    cout << "Start of addition..." << endl;

    dynamicArray<int> da;
    
    const int power = 2;
    const int n = pow(10, power);

    double max_time_per_element = 0.0;
    clock_t t1 = clock();

    for (int i = 0; i < n; i++) {
        int value = rand() % 1000;
        clock_t t1_element = clock();
        da.pushBack(value);
        clock_t t2_element = clock();

        double time_per_element = (static_cast<double>(t2_element) - t1_element) / CLOCKS_PER_SEC; // calculate time taken for this operation.

        if (time_per_element > max_time_per_element) {
            max_time_per_element = time_per_element;
            cout << max_time_per_element << "s" << " - New worst time per element at index:" << i << endl;
        }
    }

    clock_t t2 = clock();
    cout << "Time: " << (t2 - t1) / (double)CLOCKS_PER_SEC << "s" << endl;
    cout << "Average time per element: " << (t2 - t1) / (double)CLOCKS_PER_SEC / n<< "s" << endl;
    cout << "End of addition." << endl;
    cout << da.print(da) << endl;

    //// Primitive methods:
    //da[0] = 5;
    //da[1] = 3;
    //da.print(da, 2);
    //cout << da[1000] << endl;
    
    // Bubble sort:
    //clock_t t3 = clock();
    //std::cout << "Start of sorting..." << std::endl;
    //da.bubbleSort();
    //clock_t t4 = clock();
    //std::cout << "Time: " << (t4 - t3) / (double)CLOCKS_PER_SEC << "s" << std::endl;
    //std::cout << "Average time per element: " << (t4 - t3) / (double)CLOCKS_PER_SEC/n << "s" << std::endl;
    //std::cout << "End of sorting..." << std::endl;
    //da.print(da, 2);
    da.clear();
    return 0;
}
