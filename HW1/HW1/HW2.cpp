#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
protected:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    virtual ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    virtual void insertItem(int val) = 0;
    virtual void removeItem() = 0;

    void printList() const {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

class Stack : public DoublyLinkedList {
public:
    void insertItem(int val) override {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void removeItem() override {
        if (!head) return;
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
};

class Queue : public DoublyLinkedList {
public:
    void insertItem(int val) override {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void removeItem() override {
        if (!head) return;
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
};

class FileHandler {
public:
    virtual ~FileHandler() {}

    virtual void Display(const char* path) {
        ifstream file(path);
        if (!file) {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        char ch;
        while (file.get(ch)) {
            cout << ch;
        }
        cout << endl;
        file.close();
    }
};

class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path);
        if (!file) {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        char ch;
        while (file.get(ch)) {
            cout << (int)ch << " ";
        }
        cout << endl;
        file.close();
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        ifstream file(path);
        if (!file) {
            cout << "Cannot open file: " << path << endl;
            return;
        }
        char ch;
        while (file.get(ch)) {
            for (int i = 7; i >= 0; --i) {
                cout << ((ch >> i) & 1);
            }
            cout << " ";
        }
        cout << endl;
        file.close();
    }
};

int main() {
    cout << "=== Testing Task 1 (Stack & Queue) ===" << endl;

    Stack myStack;
    myStack.insertItem(10);
    myStack.insertItem(20);
    myStack.insertItem(30);
    cout << "Stack after inserts: ";
    myStack.printList();

    myStack.removeItem();
    cout << "Stack after one remove: ";
    myStack.printList();

    Queue myQueue;
    myQueue.insertItem(10);
    myQueue.insertItem(20);
    myQueue.insertItem(30);
    cout << "Queue after inserts: ";
    myQueue.printList();

    myQueue.removeItem();
    cout << "Queue after one remove: ";
    myQueue.printList();

    cout << "\n=== Testing Task 2 (File Handling) ===" << endl;

    const char* filename = "test_data.txt";
    ofstream out(filename);
    if (out) {
        out << "Hi!";
        out.close();
    }

    FileHandler baseHandler;
    cout << "Base handler (Plain text): ";
    baseHandler.Display(filename);

    AsciiFileHandler asciiHandler;
    cout << "ASCII handler (ASCII codes): ";
    asciiHandler.Display(filename);

    BinaryFileHandler binaryHandler;
    cout << "Binary handler (Binary codes): ";
    binaryHandler.Display(filename);

    return 0;
}