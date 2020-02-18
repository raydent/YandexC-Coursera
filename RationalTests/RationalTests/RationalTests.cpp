// RationalTests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class Rational {
public:
    // Р’С‹ РјРѕР¶РµС‚Рµ РІСЃС‚Р°РІР»СЏС‚СЊ СЃСЋРґР° СЂР°Р·Р»РёС‡РЅС‹Рµ СЂРµР°Р»РёР·Р°С†РёРё,
    // С‡С‚РѕР±С‹ РїСЂРѕРІРµСЂРёС‚СЊ, С‡С‚Рѕ РІР°С€Рё С‚РµСЃС‚С‹ РїСЂРѕРїСѓСЃРєР°СЋС‚ РєРѕСЂСЂРµРєС‚РЅС‹Р№ РєРѕРґ
    // Рё Р»РѕРІСЏС‚ РЅРµРєРѕСЂСЂРµРєС‚РЅС‹Р№

    Rational();
    Rational(int numerator, int denominator) {
    }

    int Numerator() const {
    }

    int Denominator() const {
    }
};
bool operator ==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}
bool operator ==(const Rational& lhs, const pair<int, int>& rhs) {
    return (lhs.Numerator() == rhs.first && lhs.Denominator() == rhs.second);
}
template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
    const string& hint)
{
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
            << " hint: " << hint;
        throw runtime_error(os.str());
    }
}

inline void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (runtime_error & e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};
void zero_denom_test() {
    Rational r(2, 0);
    AssertEqual(r.Denominator(), 0, "zero_denom, denom is zero");
    AssertEqual(r.Numerator(), 1, "zero_denom, numerator is one");
}
void default_constructor_test() {
    Rational r;
    AssertEqual(r.Denominator(), 1, "default_constructor, denom is one");
    AssertEqual(r.Numerator(), 0, "default_constructor, numerator is zero");
}
void divide_test() {
    Rational r1(6, 3);
    Rational r2(14, 2);
    Rational r3(-7, 3);
    Rational r4(-8, 2);
    Rational r5(-2, -3);
    Rational r6(-4, -2);
    AssertEqual(r1, make_pair(2, 1), "divide_test, r1 != 2 1");
    AssertEqual(r2, make_pair(7, 1), "divide_test, r2 != 7 1");
    AssertEqual(r3, make_pair(-7, 3), "divide_test, r3 != -7 3");
    AssertEqual(r4, make_pair(-4, 1), "divide_test, r4 != -4 1");
    AssertEqual(r5, make_pair(2, 3), "divide_test, r5 != 2 3");
    AssertEqual(r6, make_pair(2, 1), "divide_test, r6 != 2 1");
}
int main()
{
    TestRunner runner;
    runner.RunTest(zero_denom_test, "zero_denom_test");
    runner.RunTest(default_constructor_test, "default_constructor_test");
    runner.RunTest(divide_test, "divide_test");
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
