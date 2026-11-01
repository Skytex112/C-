#include <iostream>

size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strcpy(char* dest, const char* src) {
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


// Завдання 1
class String {
private:
    char* data;
    size_t length;

public:
    String() : data(nullptr), length(0) {}

    String(const char* str) {
        if (str) {
            length = my_strlen(str);
            data = new char[length + 1];
            my_strcpy(data, str);
        }
        else {
            data = nullptr;
            length = 0;
        }
    }

    String(const String& other) {
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            my_strcpy(data, other.data);
        }
        else {
            data = nullptr;
        }
    }

    String(String&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;  

            data = other.data;
            length = other.length;

            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    ~String() {
        delete[] data;
    }

    void print() const {
        if (data) std::cout << data;
        else std::cout << "empty";
    }
};

// Завдання 2
template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array(size_t s = 0) : size(s) {
        data = (size > 0) ? new T[size]() : nullptr;
    }

    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;

            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }
};

// Завдання 3 та 4
class Student {
public:
    class ContactInfo {
    public:
        String email;
        String phone;

        ContactInfo() = default;
        ContactInfo(const char* e, const char* p) : email(e), phone(p) {}

        ContactInfo(ContactInfo&& other) noexcept
            : email(static_cast<String&&>(other.email)),
            phone(static_cast<String&&>(other.phone)) {}

        ContactInfo& operator=(ContactInfo&& other) noexcept {
            if (this != &other) {
                email = static_cast<String&&>(other.email);
                phone = static_cast<String&&>(other.phone);
            }
            return *this;
        }
    };

private:
    String name;
    ContactInfo contacts;
    int age;

public:
    Student(const char* n, const char* e, const char* p, int a)
        : name(n), contacts(e, p), age(a) {}

    Student(Student&& other) noexcept
        : name(static_cast<String&&>(other.name)),
        contacts(static_cast<ContactInfo&&>(other.contacts)),
        age(other.age)
    {
        other.age = 0;
    }

    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            name = static_cast<String&&>(other.name);
            contacts = static_cast<ContactInfo&&>(other.contacts);
            age = other.age;

            other.age = 0;
        }
        return *this;
    }

    void print() const {
        std::cout << "Student: ";
        name.print();
        std::cout << ", Age: " << age << std::endl;
    }
};

int main() {
    std::cout << "--- String Move Test ---" << std::endl;
    String s1("Hello, World!");
    String s2(static_cast<String&&>(s1));

    std::cout << "s2: "; s2.print(); std::cout << std::endl;

    String s3;
    s3 = static_cast<String&&>(s2);
    std::cout << "s3: "; s3.print(); std::cout << std::endl;

    std::cout << "\n--- Array Move Test ---" << std::endl;
    Array<int> arr1(10);
    Array<int> arr2(static_cast<Array<int>&&>(arr1));
    Array<int> arr3;
    arr3 = static_cast<Array<int>&&>(arr2);
    std::cout << "Array move completed." << std::endl;

    std::cout << "\n--- Student Move Test ---" << std::endl;
    Student st1("Ivan Ivanov", "ivan@example.com", "123-456", 20);
    st1.print();

    Student st2(static_cast<Student&&>(st1));
    st2.print();

    Student st3("Test", "test@test.com", "000", 18);
    st3 = static_cast<Student&&>(st2);
    st3.print();

    return 0;
}