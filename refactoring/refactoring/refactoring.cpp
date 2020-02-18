#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


class Human {
private:
    const string Type, Name;
public:
    Human(string type, string name): Type(type), Name(name) {}
    virtual void Walk(string destination) const = 0;
    string Type_Name() const { return Type + ": " + Name; };
    string Type_() const { return Type; };
    string Name_() const { return Name; };
};

class Student: public Human  {
public:

    Student(string name, string favouriteSong): Human("Student", name), FavouriteSong(favouriteSong){}
    void Learn() const {
        cout << Type_Name() << " learns" << endl;
    }
    void Walk(string destination) const override {
        cout << Type_Name() << " walks to: " << destination << endl;
        cout << Type_Name() << " sings a song: " << FavouriteSong << endl;
    }
    void SingSong() {
        cout << Type_Name() << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher: public Human {
public:

    Teacher(string name, string subject): Human("Teacher", name), Subject(subject) {}

    void Walk(string destination) const override {
        cout << Type_Name() << " walks to: " << destination << endl;
    }
    void Teach() {
        cout << Type_Name() << " teaches: " << Subject << endl;
    }


private:
    string Subject;
};


class Policeman : public Human {
public:
    Policeman(string name): Human("Policeman", name){}
    void Walk(string destination) const override {
        cout << Type_Name() << " walks to: " << destination << endl;
    }
    void Check(const Human& human) {
        cout << Type_Name() << " checks " << human.Type_() + ". " + human.Type_() + "'s name is: " << human.Name_() << endl;
    }
};


void VisitPlaces(const Human& h, vector<string> places) {
    for (auto p : places) {
        h.Walk(p);
    }
}



int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
