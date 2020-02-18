#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

class Figure {
public:
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure {
private:
    int a = 0, b = 0, c = 0;
public:
    Triangle(int a_, int b_, int c_) : a(a_), b(b_), c(c_){};
    double Perimeter() override {
        return a + b + c;
    }
    double Area() override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    string Name() override {
        return "TRIANGLE";
    }
};

class Rect : public Figure {
private:
    int width = 0, height = 0;
public:
    Rect(int w, int h) : width(w), height(h){};
    double Perimeter() override {
        return (width + height) * 2;
    }
    double Area() override {
        return width * height;
    }
    string Name() override {
        return "RECT";
    }
};

class Circle : public Figure {
private:
    int r = 0;
public:
    Circle(int r_) : r(r_) {};
    double Perimeter() override {
        return 2 * 3.14 * r;
    }
    double Area() override {
        return 3.14 * r * r;
    }
    string Name() override {
        return "CIRCLE";
    }
};
shared_ptr<Figure> CreateFigure(istringstream& is) {
    string s;
    //getline(is, s, ' ');
    is >> s;
    //cout << s;
    if (s == "RECT") { 
        //printf("Here");
        int w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }
    if (s == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    if (s == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }
}
int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);
        string command;
        is >> command;
        //cout << command << endl;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}