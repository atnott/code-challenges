#pragma once
#include <stdexcept>

int find_last(int n, int step);

template<class T>
class List {
private:
    struct Node {
        Node* p_next;
        T data;
        Node(T data = T(), Node* p_next = nullptr) : data(data), p_next(p_next) {}
    };
    int size;
    Node* head;
    Node* tail;
    friend int find_last(int n, int step);
public:
    List();
    ~List();

    void clear();
    int get_size() {return size;};
    T& operator [] (const int index);

    void push_back(T data);
    void push_front(T data);

    void pop_front();
    void pop_back();

    void insert(int index, T data);
    void remove_at(int index);
	void remove_after(Node* previous);
};

template<class T>
List<T>::List() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<class T>
List<T>::~List() {
    clear();
}

template<class T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node(data);
		head->p_next = head;
        tail = head;
    }
    else {
        tail->p_next = new Node(data, head);
        tail = tail->p_next;
    }
    size++;
}

template<class T>
T& List<T>::operator [] (const int index) {

    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    int cnt = 0;
    Node* current = this->head;
    while (cnt < index) {
        current = current->p_next;
        cnt++;
    }
    return current->data;
}

template<class T>
void List<T>::pop_front() {
    if (!head) return;
    if (size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node* temp = head;
        head = head->p_next;
        tail->p_next = head;
        delete temp;
    }
    size--;
}

template<class T>
void List<T>::clear() {
    while (size) {
        pop_front();
    }
}

template<class T>
void List<T>::push_front(T data) {
    if (head == nullptr) {
        head = new Node(data);
        head->p_next = head;
        tail = head;
    }
    else {
        head = new Node(data, head);
        tail->p_next = head;
    }
    size++;
}

template<class T>
void List<T>::insert(int index, T data) {
    if (index < 0 || index > size) return;
    if (index == 0) {
        push_front(data);
    }
    else if (index == size) {
        push_back(data);
    }
    else {
        Node* previous = this->head;

        for (int i {0}; i < index - 1; i++) {
            previous = previous->p_next;
        }

        Node* new_node = new Node(data, previous->p_next);
        previous->p_next = new_node;

        size++;
    }
}

template<class T>
void List<T>::remove_at(int index) {
    if (index < 0 || index >= size) return;
    if (index == 0) {
        pop_front();
    }
    else {
        Node* previous = this->head;
        for (int i {0}; i < index - 1; i++) {
            previous = previous->p_next;
        }
        Node* to_delete = previous->p_next;

        if (to_delete == tail) {
            tail = previous;
        }

        previous->p_next = to_delete->p_next;
        delete to_delete;
        size--;
    }
}

template<class T>
void List<T>::pop_back() {
    remove_at(size - 1);
}

template<class T>
void List<T>::remove_after(typename  List<T>::Node* previous) {
    Node* to_delete = previous->p_next;
    if (to_delete == head) {
        head = to_delete->p_next;
    }
    if (to_delete == tail) {
        tail = previous;
    }
    previous->p_next = to_delete->p_next;
    delete to_delete;
    size--;
}
