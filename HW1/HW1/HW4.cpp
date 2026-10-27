#include <iostream>
#include <string>

using namespace std;

class CustomException {
private:
    const char* message;
public:
    CustomException(const char* msg) : message(msg) {}
    const char* what() const {
        return message;
    }
};

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!newNode) {
            throw CustomException("Exception: Memory allocation failed!");
        }
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop_front() {
        if (!head) {
            throw CustomException("Exception: Attempt to remove from an empty list!");
        }
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    void print() const {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

class Array {
private:
    int* data;
    int size;
    int capacity;
public:
    Array(int cap) : size(0), capacity(cap) {
        data = new int[capacity];
        if (!data) {
            throw CustomException("Exception: Memory allocation failed!");
        }
    }

    ~Array() {
        delete[] data;
    }

    void add(int val) {
        if (size >= capacity) {
            throw CustomException("Exception: Array capacity exceeded!");
        }
        data[size++] = val;
    }

    void remove() {
        if (size == 0) {
            throw CustomException("Exception: Attempt to remove from an empty array!");
        }
        size--;
    }

    int get(int index) const {
        if (index < 0 || index >= size) {
            throw CustomException("Exception: Index out of bounds!");
        }
        return data[index];
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "Task 1" << endl;
    DoublyLinkedList list;

    try {
        list.push_back(10);
        list.push_back(20);
        cout << "List after adding: ";
        list.print();

        list.pop_front();
        list.pop_front();
        cout << "List after removing all elements." << endl;

        cout << "Attempting to remove from empty list..." << endl;
        list.pop_front();
    }
    catch (const CustomException& e) {
        cout << e.what() << endl;
    }

    cout << "\nTask 2" << endl;
    try {
        Array arr(2);

        arr.add(100);
        arr.add(200);
        cout << "Array after adding elements: ";
        arr.print();

        cout << "Attempting to add beyond capacity..." << endl;
        arr.add(300);
    }
    catch (const CustomException& e) {
        cout << e.what() << endl;
    }

    try {
        Array arr2(5);
        cout << "\nAttempting to access invalid index..." << endl;
        arr2.get(10);
    }
    catch (const CustomException& e) {
        cout << e.what() << endl;
    }

    try {
        Array arr3(5);
        cout << "\nAttempting to remove from empty array..." << endl;
        arr3.remove();
    }
    catch (const CustomException& e) {
        cout << e.what() << endl;
    }

    return 0;
}