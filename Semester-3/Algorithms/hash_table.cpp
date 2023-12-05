#include <iostream>
#include <string>
#include <cmath>

using namespace std;
#include <sstream>
template <typename T>
class lista
{
public:
    friend std::ostream& operator<< (std::ostream& out, const lista& obj) {
        out << obj.to_string();
        return out;
    }
    struct Wezel {
        Wezel* prev;
        Wezel* next;
        T dane;

    };
    Wezel* head, * tail;
    int size;
public:
    lista() {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~lista(){
        clear();
    }
    void add_to_tail(const T dane) {
        if (size == 0) {
            auto* wezel = new Wezel;
            wezel->dane = dane;
            wezel->prev = nullptr;
            wezel->next = nullptr;
            tail = wezel;
            head = wezel;
        }
        else {
            auto* last = new Wezel;
            last->prev = tail;
            last->next = nullptr;
            last->dane = dane;
            tail->next = last;
            tail = last;
        }
        size++;
    }
    void add_to_head(const T dane) {
        if (size == 0) {
            Wezel* wezel = new Wezel;
            wezel->dane = dane;
            wezel->prev = nullptr;
            wezel->next = nullptr;
            tail = wezel;
            head = wezel;
        }
        else {
            Wezel* first = new Wezel;
            first->prev = nullptr;
            first->next = head;
            first->dane = dane;
            head->prev = first;
            head = first;
        }
        size++;
    }
    //wyszukanie i usuniecie elementu
    bool find_del(bool (*cmpr)(T, T), T dane) {

        Wezel* ptr = head;


        if (!size) {
            return false;
        }

        if (cmpr(tail->dane, dane) ){
            delete_head();
            return true;
        }

        if (cmpr(head->dane, dane) ){
            delete_tail();
            return true;
        }
        for (int i = 0; i < size; i++) {
            if (cmpr(ptr->dane,dane)) {
                Wezel* temp = ptr->next;
                temp->prev = ptr->prev;
                temp = ptr->prev;
                temp->next = ptr->next;
                size--;
                delete ptr;
                return true;
            }
            ptr = ptr->next;

        }
        return false;
    }

    void delete_tail() {
        if (size == 0) {
            throw std::runtime_error("Error: cannot delete from an empty list!");
        }
        else if (size == 1) {
            delete tail;
            tail = nullptr;
            head = nullptr;
        }
        else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        size--;
    }

    void delete_head() {
        if (size == 0) {
            throw std::runtime_error("Error: cannot delete from an empty list!");
        }
        else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        size--;
    }

    T return_data(int i) {
        if (i >= size) {
            throw std::out_of_range("Error: index is out of range!");
        }
        if (i < 0) {
            throw std::invalid_argument("Error: index cannot be negative!");
        }
    }

    Wezel* search_data(T value) {
        Wezel* ptr = head;
        for (int j = 0; j < size; j++) {
            if (ptr->dane == value) {
                return ptr;
            }
            ptr = ptr->next;
        }
        throw std::runtime_error("Could not find the specified value in the list!");
    }


    std::string to_string(int num_elements = 5) const
    {
        std::ostringstream str;
        str << "Size: " << size << ", Address: " << this << ", Elements: ";

        if (size == 0)
            return str.str() + "[]";

        str << "[" << head->dane;

        int count = 1;
        for (auto ptr = head->next; ptr && (count < num_elements || num_elements == -1); ptr = ptr->next, ++count)
            str << ", " << ptr->dane;

        if (num_elements != -1 && num_elements < size)
            str << ", ...";

        str << "]";
        return str.str();
    }
    void clear() {
        while (head) {
            Wezel* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

};

struct osoba
{
    int a;
    char b;
};


using namespace std;
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

private:

    T* data = nullptr;
    size_t size = 0; // size
    size_t capacity = 0; // maximum size
};


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



template <typename T>
struct wpis{
    string key;
    T value;
}; // 🙂
template <typename T>
class HashTable {
public:
    int ilosc;
    bool cmpr(wpis<int> w1, wpis<int> w2){
        return w1.value == w2.value;//🙂
    }
    HashTable();
// bez destruktora= bloat!😡😡😡🤌🤌😡😡😡

    dynamicArray<lista<wpis<int> > > da;

//funkcja hashujaca
    int hashing(string str) {
        if (str.empty()) return 1;
        char symbol = 0;
        int ascii = 0;
        int sum = 0;

        for (int i = 0; i <= str.length(); i++) {
            symbol = str[i];
            ascii = (int) symbol;
            sum += ascii * pow(31, str.length() - i); // TAKI WZOR
        }
        if ((sum % da.getSize()) < 0) {

            return (sum % da.getSize() + da.getSize()) % da.getSize();
        }
    }

    void addition(string key, T value) {
        // rehash
        // przypisac wszsytkie wartosci do tymczsowaje tablicy
        // wczesniejsza wyczyscic i przygotowac 2razy wieksza
        // wywolac hashowanie
        if (ilosc > 0.75 * da.getSize()) {
            int temp = da.getSize(); // im back
            da.reAlloc(temp*2);
        }
        wpis<T> wpisanie;
        wpisanie.key = key;
        wpisanie.value = value;
        int hash = hashing(key);

            auto ptr = da[hash].head;
            for (int j = 0; j < da[hash].size; j++) {
                if (ptr->dane.key == key) {
                   ptr->dane.value = value;
                }
                ptr = ptr->next;
            }
            da[hash].add_to_head(wpisanie);
            ilosc++;
        }


    wpis<T> *search(string key) {
        int hash = hashing(key);
        if (da[hash].head == nullptr && da[hash].head == nullptr) {
            return nullptr;
        } else { // da[hash] = lista

            auto ptr = da[hash].head;
            for (int j = 0; j < da[hash].size; j++) {
                if (ptr->dane.key == key) {
                    return &(ptr->dane);
                }
                ptr = ptr->next;
            }
            return nullptr;

        }
    }

    void clear() {
        da.clear();
        da.reAlloc(2);
    }

    string toStr() {
        string result = "";
        for (int i = 0; i < da.getSize(); i++) {
            result += "list indeks: ";
            result += i;
            for (int j = 0; j < da[j].size; j++) {
                auto ptr = da[j].head;

                result += "indeks: ";
                result += j;
                result += ptr->dane.key;
                result += "\t";
                result += ptr->dane.value;
                result += "\t";
                ptr = ptr->next;
            }

        }
    };
    bool delete_twoj_stary(string key){
        int hash = hashing(key);
        if (da[hash].head == nullptr && da[hash].head == nullptr) {
            return false;
        } else { // da[hash] = lista
            return da[hash].find_del(&HashTable::cmpr, key);

        }
    }




};
int main() {

    /* rehash ...
     (a) dodanie nowego elementu (argumenty: klucz oraz wartość — czyli inaczej dane skojarzone z
    kluczem),
    (b)️ ☪️
    (c) ☪️
    (d) ☪️
    (e) ☪️
    f ☪️
     */


    return 0;
}
