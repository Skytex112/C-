#include <iostream>
#include <string>

using namespace std;

class GeometricFigure {
protected:
    double size;
public:
    GeometricFigure(double s) : size(s) {
        cout << " [Geometry] Base figure created (size: " << size << ")" << endl;
    }
    virtual ~GeometricFigure() {}
};

class Square : virtual public GeometricFigure {
public:
    Square(double s) : GeometricFigure(s) {}
    double getSquareArea() const { return size * size; }
};

class Circle : virtual public GeometricFigure {
public:
    Circle(double d) : GeometricFigure(d) {}
    double getCircleArea() const { return 3.14159 * (size / 2) * (size / 2); }
};

class InscribedCircle : public Square, public Circle {
public:
    InscribedCircle(double s) : GeometricFigure(s), Square(s), Circle(s) {
        cout << " [Geometry] Created 'Circle inscribed in a square'" << endl;
    }

    void printFigureInfo() const {
        cout << "  Square side / Circle diameter: " << size << endl;
        cout << "  Square area: " << getSquareArea() << endl;
        cout << "  Circle area: " << getCircleArea() << endl;
    }
};

class CarComponent {
protected:
    string manufacturer;
public:
    CarComponent(const string& m) : manufacturer(m) {}
    virtual ~CarComponent() {}
};

class Engine : virtual public CarComponent {
protected:
    int horsepower;
public:
    Engine(const string& m, int hp) : CarComponent(m), horsepower(hp) {}
};

class Wheels : virtual public CarComponent {
protected:
    int radius;
public:
    Wheels(const string& m, int r) : CarComponent(m), radius(r) {}
};

class Doors : virtual public CarComponent {
protected:
    int doorsCount;
public:
    Doors(const string& m, int d) : CarComponent(m), doorsCount(d) {}
};

class Car : public Engine, public Wheels, public Doors {
private:
    string model;
public:
    Car(const string& compManufacturer, int hp, int r, int d, const string& mod)
        : CarComponent(compManufacturer), Engine(compManufacturer, hp),
        Wheels(compManufacturer, r), Doors(compManufacturer, d), model(mod) {
        cout << " [Car] Car created: " << model << endl;
    }

    void printCarInfo() const {
        cout << "  Model: " << model << " (Components manufacturer: " << manufacturer << ")" << endl;
        cout << "  Engine (HP): " << horsepower << endl;
        cout << "  Wheels radius: " << radius << "\"" << endl;
        cout << "  Doors count: " << doorsCount << endl;
    }
};

template <typename T1, typename T2>
class Base {
protected:
    T1 value1;
    T2 value2;
public:
    Base(T1 v1, T2 v2) : value1(v1), value2(v2) {}
    virtual ~Base() { cout << " ~ Base destructor" << endl; }

    void printBase() const {
        cout << "  Base fields: value1 = " << value1 << ", value2 = " << value2 << endl;
    }
};

template <typename T1, typename T2, typename T3, typename T4>
class Child : public Base<T1, T2> {
protected:
    T3 value3;
    T4 value4;
public:
    Child(T1 v1, T2 v2, T3 v3, T4 v4) : Base<T1, T2>(v1, v2), value3(v3), value4(v4) {}
    ~Child() { cout << " ~ Child destructor" << endl; }

    void printChild() const {
        this->printBase();
        cout << "  Child fields: value3 = " << value3 << ", value4 = " << value4 << endl;
    }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class Child2 : public Child<T1, T2, T3, T4> {
protected:
    T5 value5;
    T6 value6;
public:
    Child2(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6)
        : Child<T1, T2, T3, T4>(v1, v2, v3, v4), value5(v5), value6(v6) {}
    ~Child2() { cout << " ~ Child2 destructor" << endl; }

    void printChild2() const {
        this->printChild();
        cout << "  Child2 fields: value5 = " << value5 << ", value6 = " << value6 << endl;
    }
};

int main() {
    cout << "=== Testing Tasks 1 and 3 (Figures) ===" << endl;
    InscribedCircle myCircle(10.0);
    myCircle.printFigureInfo();
    cout << endl;

    cout << "=== Testing Tasks 2 and 3 (Car) ===" << endl;
    Car myCar("Toyota Motors", 250, 18, 4, "Toyota Camry");
    myCar.printCarInfo();
    cout << endl;

    cout << "=== Testing Task 4 (Template inheritance) ===" << endl;
    Child2<int, double, char, string, bool, float> myTemplateObj(
        42, 3.14, 'Z', "Hello C++", true, 9.99f
    );
    myTemplateObj.printChild2();
    cout << "------------------------------------------" << endl;

    return 0;
}