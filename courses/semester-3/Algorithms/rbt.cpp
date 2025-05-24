#include <iostream>
#include <cmath>
#include <ctime>
#include "red_black_tree.h"

using namespace std;

int main() {
    const int MAX_ORDER = 2;
    RedBlackTree<int> rbt;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            rbt.insert(rand() % 10000000);
        }
        clock_t t2 = clock();

        cout << "Tree after inserting " << n << " elements:\n";
        cout << rbt.to_str();  // Using the to_str method to display the tree
        cout << "\n";

        double insertTime = (double)(t2 - t1) / CLOCKS_PER_SEC;

        cout << "Time taken for insertion: " << insertTime << " seconds\n";

        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            RedBlackTree<int>::Node* result = rbt.search(rbt.root, rand() % 10000000);
            if (result != nullptr) {
                hits++;
            }
        }
        t2 = clock();

        double searchTime = (double)(t2 - t1) / CLOCKS_PER_SEC;

        cout << "Time taken for searching: " << searchTime << " seconds\n";
        cout << "Number of hits: " << hits << endl;

        int height = rbt.calculateHeight(rbt.root);

        cout << "Height: " << height << endl;
        cout << "Height/log2(n+1): " << height / log2(n + 1) << endl;

        rbt.clear(rbt.root);  // reset
    }

    return 0;
}
