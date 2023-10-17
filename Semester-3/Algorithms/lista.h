#pragma once
#include <iostream>
using namespace std;
#include <string> 
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

	void add_to_tail(const T dane) {
		if (size == 0) {
			Wezel* wezel = new Wezel;
			wezel->dane = dane;
			wezel->prev = nullptr;
			wezel->next = nullptr;
			tail = wezel;
			head = wezel;
		}
		else {
			Wezel* last = new Wezel;
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
