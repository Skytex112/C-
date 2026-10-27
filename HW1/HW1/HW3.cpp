#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Employer {
protected:
    string name;
public:
    Employer(const string& n) : name(n) {}
    virtual ~Employer() {}
    virtual void Print() const = 0;
};

class President : public Employer {
public:
    President(const string& n) : Employer(n) {}
    void Print() const override {
        cout << "President: " << name << endl;
    }
};

class Manager : public Employer {
private:
    string department;
public:
    Manager(const string& n, const string& dep) : Employer(n), department(dep) {}
    void Print() const override {
        cout << "Manager: " << name << " (Department: " << department << ")" << endl;
    }
};

class Worker : public Employer {
private:
    string position;
public:
    Worker(const string& n, const string& pos) : Employer(n), position(pos) {}
    void Print() const override {
        cout << "Worker: " << name << " (Position: " << position << ")" << endl;
    }
};

class FigureArea {
public:
    virtual ~FigureArea() {}
    virtual double Area() const = 0;
};

class RectArea : public FigureArea {
private:
    double width, height;
public:
    RectArea(double w, double h) : width(w), height(h) {}
    double Area() const override {
        return width * height;
    }
};

class CircleArea : public FigureArea {
private:
    double radius;
public:
    CircleArea(double r) : radius(r) {}
    double Area() const override {
        return 3.14159 * radius * radius;
    }
};

class RightTriangleArea : public FigureArea {
private:
    double base, height;
public:
    RightTriangleArea(double b, double h) : base(b), height(h) {}
    double Area() const override {
        return 0.5 * base * height;
    }
};

class TrapezoidArea : public FigureArea {
private:
    double a, b, height;
public:
    TrapezoidArea(double a, double b, double h) : a(a), b(b), height(h) {}
    double Area() const override {
        return 0.5 * (a + b) * height;
    }
};

class Shape {
public:
    virtual ~Shape() {}
    virtual void Show() const = 0;
    virtual void Save(ofstream& out) const = 0;
    virtual void Load(ifstream& in) = 0;
};

class Square : public Shape {
private:
    double x, y, side;
public:
    Square(double x = 0, double y = 0, double s = 0) : x(x), y(y), side(s) {}
    void Show() const override {
        cout << "Square: Top-Left(" << x << ", " << y << "), Side=" << side << endl;
    }
    void Save(ofstream& out) const override {
        out << 1 << " " << x << " " << y << " " << side << endl;
    }
    void Load(ifstream& in) override {
        in >> x >> y >> side;
    }
};

class Rectangle : public Shape {
private:
    double x, y, width, height;
public:
    Rectangle(double x = 0, double y = 0, double w = 0, double h = 0)
        : x(x), y(y), width(w), height(h) {}
    void Show() const override {
        cout << "Rectangle: Top-Left(" << x << ", " << y << "), Width=" << width << ", Height=" << height << endl;
    }
    void Save(ofstream& out) const override {
        out << 2 << " " << x << " " << y << " " << width << " " << height << endl;
    }
    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
private:
    double cx, cy, radius;
public:
    Circle(double cx = 0, double cy = 0, double r = 0) : cx(cx), cy(cy), radius(r) {}
    void Show() const override {
        cout << "Circle: Center(" << cx << ", " << cy << "), Radius=" << radius << endl;
    }
    void Save(ofstream& out) const override {
        out << 3 << " " << cx << " " << cy << " " << radius << endl;
    }
    void Load(ifstream& in) override {
        in >> cx >> cy >> radius;
    }
};

class Ellipse : public Shape {
private:
    double x, y, width, height;
public:
    Ellipse(double x = 0, double y = 0, double w = 0, double h = 0)
        : x(x), y(y), width(w), height(h) {}
    void Show() const override {
        cout << "Ellipse: Bounding Box Top-Left(" << x << ", " << y << "), Width=" << width << ", Height=" << height << endl;
    }
    void Save(ofstream& out) const override {
        out << 4 << " " << x << " " << y << " " << width << " " << height << endl;
    }
    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

int main() {
    cout << "=== Testing Task 1 (Employers) ===" << endl;
    President p("John Doe");
    Manager m("Alice Smith", "Sales");
    Worker w("Bob Johnson", "Developer");

    Employer* employers[] = { &p, &m, &w };
    for (int i = 0; i < 3; ++i) {
        employers[i]->Print();
    }

    cout << "\n=== Testing Task 2 (Figure Areas) ===" << endl;
    RectArea rect(5.0, 4.0);
    CircleArea circ(3.0);
    RightTriangleArea tri(4.0, 3.0);
    TrapezoidArea trap(2.0, 4.0, 5.0);

    FigureArea* figures[] = { &rect, &circ, &tri, &trap };
    const string figNames[] = { "Rectangle", "Circle", "Right Triangle", "Trapezoid" };

    for (int i = 0; i < 4; ++i) {
        cout << figNames[i] << " area: " << figures[i]->Area() << endl;
    }

    cout << "\n=== Testing Task 3 (Shapes I/O) ===" << endl;

    vector<Shape*> originalShapes;
    originalShapes.push_back(new Square(0, 0, 5));
    originalShapes.push_back(new Rectangle(1, 1, 10, 20));
    originalShapes.push_back(new Circle(5, 5, 15));
    originalShapes.push_back(new Ellipse(2, 2, 8, 4));

    ofstream outFile("shapes_data.txt");
    if (outFile) {
        for (size_t i = 0; i < originalShapes.size(); ++i) {
            originalShapes[i]->Save(outFile);
        }
        outFile.close();
        cout << "Shapes successfully saved to shapes_data.txt" << endl;
    }

    vector<Shape*> loadedShapes;
    ifstream inFile("shapes_data.txt");
    if (inFile) {
        int type;
        while (inFile >> type) {
            Shape* s = nullptr;
            if (type == 1) s = new Square();
            else if (type == 2) s = new Rectangle();
            else if (type == 3) s = new Circle();
            else if (type == 4) s = new Ellipse();

            if (s) {
                s->Load(inFile);
                loadedShapes.push_back(s);
            }
        }
        inFile.close();
        cout << "Shapes successfully loaded from shapes_data.txt" << endl;
    }

    cout << "\nLoaded Shapes Information:" << endl;
    for (size_t i = 0; i < loadedShapes.size(); ++i) {
        loadedShapes[i]->Show();
    }

    for (size_t i = 0; i < originalShapes.size(); ++i) {
        delete originalShapes[i];
    }
    for (size_t i = 0; i < loadedShapes.size(); ++i) {
        delete loadedShapes[i];
    }

    return 0;
}