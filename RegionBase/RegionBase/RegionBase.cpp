// RegionBase.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
using namespace std;*/

#include <map>
#include <tuple>
#include <vector>

using namespace std;

bool operator<(const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
        tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    int result = 0;
    map<Region, int> repetition_count;
    for (const Region& region : regions) {
        result = max(result, ++repetition_count[region]);
    }
    return result;
}


/*enum class Lang {
    DE, FR, IT
};
struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};*/
/*bool operator < (const Region& lhs, const Region& rhs) {
    return make_tuple(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
        make_tuple(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}
int FindMaxRepetitionCount(const vector<Region>& regions) {
    map<Region, int> m;
    for (const auto& i : regions) {
        if (m.count(i) != 0) {
            m[i] += 1;
        }
        else
            m[i] = 1;
    }
    int sum = 0;
    for (const auto& i : m) {
        if (i.second > sum) {
            sum = i.second;
        }
    }
    return sum;
}*/
    
//using namespace std;



/*int main() {
    cout << FindMaxRepetitionCount({
     {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     },
        }) << endl;
    cout << FindMaxRepetitionCount({
     {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Moscow",
         "Toulouse",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         31
     },
        }) << endl;
}*/

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
