#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


class Human {
private:
    const string Type, Name;
public:
    Human(const string& type, const string& name) : Type(type), Name(name) {}
    virtual void Walk(const string& destination) const {
        cout << Type_Name() << " walks to: " << destination << endl;
    }
    string Type_Name() const { return Type + ": " + Name; };
    string Type_() const { return Type; };
    string Name_() const { return Name; };
};

class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong) : Human("Student", name), FavouriteSong(favouriteSong) {}
    void Learn() const {
        cout << Type_Name() << " learns" << endl;
    }
    void Walk(const string& destination) const override {
        cout << Type_Name() << " walks to: " << destination << endl;
        cout << Type_Name() << " sings a song: " << FavouriteSong << endl;
    }
    void SingSong() const {
        cout << Type_Name() << " sings a song: " << FavouriteSong << endl;
    }

private:
   const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human("Teacher", name), Subject(subject) {}
    void Teach() const {
        cout << Type_Name() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human("Policeman", name) {}
    void Check(const Human& human) const {
        cout << Type_Name() << " checks " << human.Type_() + ". " + human.Type_() + "'s name is: " << human.Name_() << endl;
    }
};


void VisitPlaces(Human& h, const vector<string>& places) {
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