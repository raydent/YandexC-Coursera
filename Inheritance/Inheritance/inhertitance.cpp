#include <iostream>

using namespace std;

class Animal {
public:

    Animal(string s): Name(s) {

    }
    const string Name;
};


class Dog: public Animal {
public:

    Dog(string s): Animal(s) {

    }
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};


int main() {
    Dog g("pluto");
    g.Bark();
}