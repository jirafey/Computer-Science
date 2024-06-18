#include <iostream>
#include <vector>

//     std::vector<int> result;
// int num1;
// int var_num;
// int *result_arr = new int [var_num+1];
// int *input_times(int var_num) {
//     for (int i=0; i< var_num; i++) {
//         int *result_arr = new int [var_num+1];
//         cout << "Enter a positive integer" << endl;
//         cin >> num1;
//         if (num1 < 0) {
//             continue;
//         }
//         else {
//             result.push_back(num1);
//             result_arr[i] = num1; 
//             printf("%p\n", result[i]);
//             printf("%p\n", result_arr[i]);

//             continue;
//         } 

//     return result_arr;
//     }

using namespace std;
int num1, num2, num3;
int * addresses[3] = {&num1,&num2, &num3};
int * dodatnie_liczby(int var_num) {
int *ptrarray = new int [var_num+1];

    for (int i=0; i< var_num; i++) {
        cout << "Enter positive integers" << endl;
        cin >> num1;
        if (num1 < 0) {
            continue;
        }
        else {
            addresses[i] = &num1;
            ptrarray[i] = *addresses[i];
        } 
    } 
        return  addresses[3+1];
}

void zad2(){
    dodatnie_liczby(3);
    cout << *addresses[0]+*addresses[1]+*addresses[2] <<endl;
}
int main(){

zad2();
//     dodatnie_liczby(3);

// cout << *addresses[0]<<endl;
// cout << *addresses[1]<<endl;
// cout << *addresses[2]<<endl;


//     input_times(3);

// int num1 = result.at(0);
// int num2 = result.at(1);
// int num3 = result.at(2);

// int sum = num1+num2+num3;

// cout << sum <<endl <<  num1 <<endl << num2 <<endl << num3 << endl;
}