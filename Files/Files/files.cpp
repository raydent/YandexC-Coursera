#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct Student {
	string name;
	string surname;
	long int year;
	long int month;
	long int day;
};
int main() {

	int N, M;
	cin >> N;
	vector<Student> students;
	while (N > 0) {
		N--;
		Student temp;
		cin >> temp.name >> temp.surname >> temp.day >> temp.month >> temp.year;
		students.push_back(temp);
	}
	cin >> N;
	while (N > 0) {
		N--;
		string op_code;
		cin >> op_code;
		if (op_code == "name") {
			int num;
			cin >> num;
			num--;
			if (num < students.size()) {
				cout << students[num].name << " " << students[num].surname << endl;
			}
			else {
				cout << "bad request" << endl;
			}
		}
		else if (op_code == "date") {
			int num;
			cin >> num;
			num--;
			if (num < students.size()) {
				cout << students[num].day << "." << students[num].month << "." << students[num].year << endl;
			}
			else {
				cout << "bad request" << endl;
			}
		}
		else {
			cout << "bad request" << endl;
			int num;
			cin >> num;
		}
	}
}