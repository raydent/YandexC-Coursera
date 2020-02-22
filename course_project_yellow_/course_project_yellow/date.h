#pragma once
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>
using namespace std;






class Date {
public:
    Date();
    Date(int new_year, int new_month, int new_day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int year;
    int month;
    int day;
};
//Date ParseDate(istringstream& date_stream);
Date ParseDate(istream&);
bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
ostream& operator<<(ostream& stream, const Date& date);

//Date ParseDate(const string& date);
