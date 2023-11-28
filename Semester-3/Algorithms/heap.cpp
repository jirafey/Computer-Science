#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

template <typename T>
class Heap {
private:
    bool (*compare)(T, T);

public:
    Heap(bool (*comp)(T, T))
            : compare{comp},
              array{new T[2]},
              size{2},
              capacity{0} {}

    ~Heap() {
        clear();
    }

    void insert(T value) {
        if (capacity == size) {
            resize();
        }

        array[capacity++] = value;
        heapify_up(capacity - 1);
    }

    T extract_max() {
        if (capacity == 0) {
            std::cerr << "Heap is empty" << std::endl;
            exit(1);
        }

        T max = array[0];
        array[0] = array[--capacity];
        heapify_down(0);
        return max;
    }

    void clear() {
        delete[] array;
        array = new T[2];
        size = 2;
        capacity = 0;
    }

    std::string to_str(int maxElements) {
        std::string str;
        int limit = std::min(maxElements, capacity);

        for (int i = 0; i < limit; i++) {
            if (2 * i + 1 < limit) {
                str += "(P)" + std::to_string(array[i]) + ": (L)" + std::to_string(array[2 * i + 1]) + "\t";
            }
            if (2 * i + 2 < limit) str += "(R)" + std::to_string(array[2 * i + 2]) + "\t";
            str += "\n";
        }
        return str;
    }



private:
    T* array;
    int size;
    int capacity;

    void resize() {
        T* newArray = new T[size * 2];
        for (int i = 0; i < capacity; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        size *= 2;
    }

    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (compare(array[index], array[parent])) {
                std::swap(array[index], array[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < capacity && compare(array[left], array[largest])) {
                largest = left;
            }

            if (right < capacity && compare(array[right], array[largest])) {
                largest = right;
            }

            if (largest != index) {
                std::swap(array[index], array[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }
};

int main() {
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_int_distribution<int> distribution(1, (1 << 24) + (1 << 23));

    const int MAX_ORDER = 7;

    for (int order = 1; order <= MAX_ORDER; ++order) {
        const int count = std::pow(10, order);
        Heap<int> max_heap([](int a, int b) {
            return a > b;
        });  //

        auto insert_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; ++i) {
            int randomNumber = distribution(generator);
            max_heap.insert(randomNumber);
        }
        auto insert_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> insert_duration = insert_end - insert_start;
        std::cout << "Insertion Time for order " << order << ": " << insert_duration.count() << " seconds" << std::endl;

        std::cout << "Inserted:\n" << max_heap.to_str(10);

        auto extract_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; ++i) {
            max_heap.extract_max();
        }
        auto extract_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> extract_duration = extract_end - extract_start;
        std::cout << "Extraction Time for order " << order << ": " << extract_duration.count() << " seconds" << std::endl;

        max_heap.clear();
    }

    return 0;
}
