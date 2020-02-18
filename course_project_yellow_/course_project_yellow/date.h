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
    // ����������� ����������� ����������, ���� ��� ��������� �����������
    Date(int new_year, int new_month, int new_day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    // ������������� ��� ������, ��� ������� ��� ����� ���������� �� <:
    // �������� ������ �� ����, ������ � ��� ��� ������ ���� � ������� ��
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() <<
        "-" << setw(2) << setfill('0') << date.GetMonth() <<
        "-" << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

Date ParseDate(const string& date);
Date ParseDate(istringstream& date_stream);