#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), list_size(0) {
	Node* current = other.head;
	while (current) {
		push_back(current->value);
		current = current->next;
	}
}

LinkedList::LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), list_size(other.list_size) {
	other.head = nullptr;
	other.tail = nullptr;
	other.list_size = 0;
}

LinkedList::~LinkedList() {
	clear();
}

void LinkedList::insert(int value) {
	Node* new_node = new Node(value);
	if (is_empty()) {
		head = tail = new_node;
	} else {
		new_node->next = head;
		head = new_node;
	}
	list_size++;
}

void LinkedList::push_back(int value) {
	Node* new_node = new Node(value);
	if (is_empty()) {
		head = tail = new_node;
	} else {
		tail->next = new_node;
		tail = new_node;
	}
	list_size++;
}

int LinkedList::pop_front() {
	if (is_empty()) throw std::out_of_range("List is empty");
	Node* temp = head;
	int value = head->value;
	head = head->next;
	delete temp;
	list_size--;
	if (is_empty()) tail = nullptr;
	return value;
}

int LinkedList::pop_back() {
	if (is_empty()) throw std::out_of_range("List is empty");

	if (head == tail) {
		int value = head->value;
		delete head;
		head = tail = nullptr;
		list_size--;
		return value;
	}

	Node* current = head;
	while (current->next != tail) {
		current = current->next;
	}

	int value = tail->value;
	delete tail;
	tail = current;
	tail->next = nullptr;
	list_size--;
	return value;
}

bool LinkedList::is_empty() const {
	return list_size == 0;
}

int LinkedList::front() const {
	if (is_empty()) throw std::out_of_range("List is empty");
	return head->value;
}

int LinkedList::back() const {
	if (is_empty()) throw std::out_of_range("List is empty");
	return tail->value;
}

int LinkedList::get(int index) const {
	if (index >= list_size) throw std::out_of_range("Index out of range");
	Node* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	return current->value;
}

void LinkedList::clear() {
	while (!is_empty()) {
		pop_front();
	}
}

int LinkedList::size() const {
	return list_size;
}

std::string LinkedList::to_string() const {
	std::string result = "[";
	Node* current = head;
	while (current) {
		result += std::to_string(current->value);
		if (current->next) result += ", ";
		current = current->next;
	}
	result += "]";
	return result;
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current) {
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        list_size = other.list_size;
        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;
    }
    return *this;
}

void LinkedList::swap(int index1, int index2) {
	if (index1 >= list_size || index2 >= list_size) throw std::out_of_range("Index out of range");
	if (index1 == index2) return;

	Node* node1 = head;
	Node* node2 = head;
	for (int i = 0; i < index1; ++i) {
		node1 = node1->next;
	}
	for (int i = 0; i < index2; ++i) {
		node2 = node2->next;
	}

	std::swap(node1->value, node2->value);
}


void sort(LinkedList& list) {
	if (list.size() < 2) return;	
	bool swapped;

	for(int i = 0; i < list.size() - 1; ++i) {
		swapped = false;
		for(int j = 0; j < list.size() - i - 1; ++j) {
			if (list.get(j) > list.get(j + 1)) {
				list.swap(j, j + 1);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}


