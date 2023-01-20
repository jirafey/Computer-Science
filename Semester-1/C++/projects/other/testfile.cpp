// #include <math.h>
// #include <iostream>
// using namespace std;

// int main(){
//     double reesult;
//     double a;
//     double b;
//     char op;

//     cout << "Input value for the first number" << endl;
//     cin >> a;
//     cout << "Input value for the second number" << endl;
//     cin >> b;



// double result = a;
//         for (int i = b; i >0; i--){
//             result*=i;
//         }
//         return result;
//         printf("%lf", result);
//         }
#include <iostream>
using namespace std;
int main(int n){
int result = 1;


for (int i = 1; i <= n; i++){
    result= result*i;
    cout << result <<endl;
}
return 0;
}
