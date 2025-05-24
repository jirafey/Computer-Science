#pragma once
using namespace std;
#include <string>
template<typename T>
class dynamicArray
{
public:
    dynamicArray() {
        reAlloc(2);
    }

    void pushBack(const T& value) {
        if (size >= capacity) {
            reAlloc(capacity*2); // 2
        }
        data[size] = value; // index is already counted + 1
        size++;
    }

    const T& operator[](size_t index) const { // just get the const value of said index
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index){ // replace
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }

    void bubbleSort() {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = 0; j < size - i - 1; j++) { // already sorted (-i)
                if (data[j] > data[j + 1]) {
                    T temp = data[j]; // save data[j]
                    data[j] = data[j + 1];
                    data[j + 1] = temp; // use saved data[j]
                }
            }
        }
    }

    void clear() { 
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    string print(const dynamicArray<T>& da) {
        string str = "\n*****************************************\nElements: ";
        for (size_t i = 0; i < da.getSize()-1; i++)
            str += "\n" + to_string(da[i]);
        str += "\n*****************************************\nSize: \n" + to_string(size) + "\nCapacity: \n" + to_string(capacity);
        return str;
    }

    string print(const dynamicArray<T>& da, size_t max) {
        string str = "\n*****************************************\n";
        str += "First " + to_string(max)+ " elements:";
        for (size_t i = 0; i < max; i++)
            str += "\n" + to_string(da[i]);
        str += "\n*****************************************\nSize: \n" + to_string(size) + "\nCapacity: \n" + to_string(capacity);
        return str;
    }

private:
    void reAlloc(size_t newCapacity) {
        T* newData = new T[newCapacity];
        if (newCapacity < size) {
            size = newCapacity;
        }

        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data; // delete the previous version of array with previous capacity
        data = newData; // use new data
        capacity = newCapacity; // adjust capacity
    }

    T* data = nullptr;
    size_t size = 0; // size
    size_t capacity = 0; // maximum size
};
