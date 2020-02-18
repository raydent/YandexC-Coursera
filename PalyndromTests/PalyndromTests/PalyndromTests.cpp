// PalyndromTests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;
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
//bool IsPalindrom(const string& s);

void empty_string_test() {
    string s;
    Assert(IsPalindrom(" "), "empty_string_test 1");
    Assert(IsPalindrom(s), "empty_string test 2");
    Assert(IsPalindrom(""), "empty string is a palindrome");
    Assert(IsPalindrom("a"), "one letter string is a palindrome");
}
void one_symbol_test() {
    string s1 = "a";
    string s2 = "z";
    string s3 = "7";
    string s4 = "&";
    Assert(IsPalindrom(s1), "one_symbol_test a");
    Assert(IsPalindrom(s2), "one_symbol_test z");
    Assert(IsPalindrom(s3), "one_symbol_test 7");
    Assert(IsPalindrom(s4), "one_symbol_test &");
}
void polyndrom_tests() {
    string s1 = "AAA";//true
    string s2 = "A A";//true
    string s3 = "bAA";//wrong
    string s4 = "AAb";//wrong
    string s5 = " AA";//wrong
    string s6 = "ABAAABA";//true
    string s7 = "A AAAAA";//wrong
    string s8 = "ABAAAAA";//wrong
    string s9 = ",,,,";
    
    Assert(IsPalindrom(s1), "polyndrom_tests AAA");
    Assert(IsPalindrom(s2), "polyndrom_tests A A");
    Assert(!IsPalindrom(s3), "polyndrom_tests bAA");
    Assert(!IsPalindrom(s4), "polyndrom_tests AAb");
    Assert(!IsPalindrom(s5), "polyndrom_tests  AA");
    Assert(IsPalindrom(s6), "polyndrom_tests ABAAABA");
    Assert(!IsPalindrom(s7), "polyndrom_tests A AAAA");
    Assert(!IsPalindrom(s8), "polyndrom_tests ABAAAAA");
    Assert(IsPalindrom(s9), "polyndrom_tests ,,,,");
}

int main()
{
    TestRunner r;
    r.RunTest(empty_string_test, "empty_string_test");
    r.RunTest(one_symbol_test, "one_symbol_test");
    r.RunTest(polyndrom_tests, "polyndrom tests");
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
