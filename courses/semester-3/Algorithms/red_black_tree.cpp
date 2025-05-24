#include <iostream>
#include <cmath>
using namespace std;
#include "red_black_tree.h"

struct testStruct {
    int value;
    std::string data;

    bool operator>(const testStruct& other) const {
        return value > other.value;
    }

};

bool operator==(const testStruct& lhs, const testStruct& rhs) {
    return lhs.value == rhs.value;
}

bool operator<(const testStruct& lhs, const testStruct& rhs) {
    return lhs.value < rhs.value;
}

std::string custom_to_string(const testStruct& obj) {
    return std::to_string(obj.value) + " " + obj.data;
}

int main() {
    const int MAX_ORDER = 7;
    RBT<testStruct> *rbt = new RBT<testStruct>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            testStruct so = {rand() % 10000000, ("Test"+ to_string(i))};
            rbt->insert(so);
        }
        clock_t t2 = clock();
        std::cout << "Tree after inserting " << n << " elements:\n"
                  << rbt->to_string(rbt->root) << std::endl;

        double insertTime = (double)(t2 - t1) / CLOCKS_PER_SEC;

        std::cout << "Time taken for insertion: " << insertTime << " seconds\n";

        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            testStruct so = {rand() % 10000000, ("Test"+ to_string(i))};
            RBT<testStruct>::Node* result = rbt->search(rbt->root, so);
            if (result != nullptr) {
                hits++;
            }
        }
        t2 = clock();

        double searchTime = (double)(t2 - t1) / CLOCKS_PER_SEC;

        std::cout << "Time taken for searching: " << searchTime << " seconds\n";

        std::cout << "Number of hits: " << hits << std::endl;
        std::cout << "h" << rbt->calculateHeight(rbt->root) << std::endl;
        std::cout << "h/log2 (n+1) " << rbt->calculateHeight(rbt->root) / log2(n + 1) << std::endl;

        rbt->clear(rbt->root);

    }
    return 0;
}