template<class T>
class List {
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
private:

    template<class K>
    class Node {
    public:
        Node* p_next;
        K data;
        Node(K data = K(), Node* p_next = nullptr) : data(data), p_next(p_next) {}
    };
    int size;
    Node<T>* head;
};

template<class T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

template<class T>
List<T>::~List() {
    clear();
}

template<class T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
    }
    else {
        Node<T>* current = this->head;
        while (current->p_next != nullptr) {
            current = current->p_next;
        }
        current->p_next = new Node<T>(data);
    }
    size++;
}

template<class T>
T& List<T>::operator [] (const int index) {
    int cnt = 0;
    Node<T>* current = this->head;
    while (current != nullptr) {
        if (cnt == index) {
            return current->data;
        }
        current = current->p_next;
        cnt++;
    }
}

template<class T>
void List<T>::pop_front() {
    Node<T>* temp = head;
    head = head->p_next;
    delete temp;
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
    head = new Node<T>(data, head);
    size++;
}

template<class T>
void List<T>::insert(int index, T data) {
    if (index < 0 || index >= size) return;
    if (index == 0) {
        push_front(data);
    }
    else {
        Node<T>* previous = this->head;

        for (int i {0}; i < index - 1; i++) {
            previous = previous->p_next;
        }

        Node<T>* new_node = new Node<T>(data, previous->p_next);
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
        Node<T>* previous = this->head;
        for (int i {0}; i < index - 1; i++) {
            previous = previous->p_next;
        }
        Node<T>* to_delete = previous->p_next;
        previous->p_next = to_delete->p_next;
        delete to_delete;
        size--;
    }
}

template<class T>
void List<T>::pop_back() {
    remove_at(size - 1);
}