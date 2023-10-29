#pragma once
#include <iostream>
using namespace std;
template <typename T> 

class lista
{
public:
	struct Wezel {
		Wezel* prev;
		Wezel* next;
		T dane;

	};
	Wezel* head, *tail;
	int size;
public:
	lista(){
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	void add_to_tail(const T dane) {
		if (size == 0) {
			size++;
			Wezel* wezel = new Wezel;
			wezel->dane = dane;
			wezel->prev = nullptr;
			wezel->next = nullptr;
			tail = wezel;
			head = wezel;
		}
		else {
			size++;
			Wezel* last = new Wezel;
			last->prev = tail;
			last->next = nullptr;
			last->dane = dane;
			tail->next = last;
			tail = last;
		}

	}
	void add_to_head(const T dane) {
		if (size == 0) {
			size++;
			Wezel* wezel = new Wezel;
			wezel->dane = dane;
			wezel->prev = nullptr;
			wezel->next = nullptr;
			tail = wezel;
			head = wezel;
		}
		else {
			size++;
			Wezel* first = new Wezel;
			first->prev = nullptr;
			first->next = head;
			first->dane = dane;
			head->prev = first;
			head = first;
		}
	}
	void delete_tail() {
		if (size == 0) {
			return;
		}
		else if (size == 1) {
			size--;
			delete tail;
			tail = nullptr;
			head = nullptr;
		}
		else {
			size--;
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
	}
	void delete_head() {
		if (size == 0) {
			return;
		}
		else if (size == 1) {
			size--;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			size--;
			head = head->next;
			delete head->prev;
			head->prev = nullptr;

		}
	}
	T return_data(int i){
		if (i > size ) {
			cout << "Error: index is out of range! Length of the list: ";
			return size;
		}
		if (i < 0) {
			cout << "Error: index cannot be negative! Index: ";
			return i;
		}
		else {
			Wezel* ptr = head;
			for (int j = 0; j < i; j++) {
				ptr = ptr->next;
			}
			return ptr->dane;
				
		}
	}
	Wezel* search_data(T value) {
		Wezel* ptr = head;
		for (int j = 0; j < size; j++) {
			
			if (ptr->dane == value) {
				return  ptr;
			}
			ptr = ptr->next;
		}
		cout << "Could not find the specified value in the list, value: " << value << endl;
		return nullptr;
	}
};
