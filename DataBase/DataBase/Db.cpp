#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;
struct Date {
	Date() {
		Year = 0;
		Day = 0;
		Month = 0;
	}
	Date(int Y, int M, int D) {
		if (!(M >= 1 && M <= 12)) {
			throw invalid_argument("Month value is invalid: " + to_string(M));
		}
		else if (!(D >= 1 && D <= 31)) {
			throw invalid_argument("Day value is invalid: " + to_string(D));
		}
		Year = Y;
		Month = M;
		Day = D;
	}
	int Year, Day, Month;
};
bool makedate1(stringstream& stream, Date& d) {
	char der1, der2;
	int Year, Month, Day;
	string s1;
	getline(stream, s1, ' ');
	stringstream stream1;
	stream1 << s1;
	if (stream1 >> Year >> der1 >> Month >> der2 >> Day) {
		if (der1 == '-' && der2 == '-') {
			if (stream1.peek() == EOF || stream1.peek() == ' ' || stream1.peek() == '\n') {
				d = Date(Year, Month, Day);
				return true;
			}
		}
	}
	//s += to_string(Year) + der1 + to_string(Month) + der2 + to_string(Day);
	throw invalid_argument("Wrong date format: " + s1);
	return false;
}
bool makedate(stringstream& stream, Date& d) {
	char c, b, a;
	int sign = 1;
	int Year, Month, Day;
	string temp;
	string s = "Wrong date format: ";
	if (!(stream.peek() == '+' || stream.peek() == '-' || isdigit(stream.peek()))) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	if (stream.peek() == '+' || stream.peek() == '-') {
		stream >> c;
		if (c == '-') {
			sign = -1;
		}
		s += c;
	}
	if (!isdigit(stream.peek())) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	stream >> Year;
	Year *= sign;
	sign = 1;
	s += to_string(Year);
	if (stream.peek() != '-') {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	stream.ignore(1);
	s += '-';
	if (!(stream.peek() == '+' || stream.peek() == '-' || isdigit(stream.peek()))) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	if (stream.peek() == '+' || stream.peek() == '-') {
		stream >> c;
		if (c == '-') {
			sign = -1;
		}
		s += c;
	}
	if (!isdigit(stream.peek())) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	stream >> Month;
	Month *= sign;
	sign = 1;
	s += to_string(Month);
	if (stream.peek() != '-') {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	stream.ignore(1);
	s += '-';
	if (!(stream.peek() == '+' || stream.peek() == '-' || isdigit(stream.peek()))) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	if (stream.peek() == '+' || stream.peek() == '-') {
		stream >> c;
		if (c == '-') {
			sign = -1;
		}
		s += c;
	}
	if (!isdigit(stream.peek())) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	stream >> Day;
	s += to_string(Day);
	Day *= sign;
	if (stream.peek() != ' ' && stream.peek() != '\n' && stream.peek() != EOF) {
		getline(stream, temp, ' ');
		s += temp;
		throw invalid_argument(s);
		return false;
	}
	d = Date(Year, Month, Day);
	return true;
}
bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.Year < rhs.Year) {
		return true;
	}
	if (lhs.Year == rhs.Year) {
		if (lhs.Month < rhs.Month) {
			return true;
		}
		if (lhs.Month == rhs.Month) {
			if (lhs.Day < rhs.Day) {
				return true;
			}
			if (lhs.Day == rhs.Day) {
				return false;
			}
			return false;
		}
		return false;
	}
	return false;
}


class DateBase {
	map<Date, set<string>> db;
public:
	void Add(int year, int month, int day, string s) {
		Date temp;
		try {
			temp = Date(year, month, day);
		}
		catch(exception& ex) {
			string s = ex.what();
			throw invalid_argument(s);
			return;
		}
		db[temp].insert(s);
	}
	void Del(int year, int month, int day) {
		Date temp;
		try {
			temp = Date(year, month, day);
		}
		catch (exception & ex) {
			throw invalid_argument(ex.what());
			return;
		}
		//cout << temp.Year << temp.Month << temp.Day << endl;
		int num = 0;
		num = db[temp].size();
		db.erase(temp);
		cout << "Deleted " + to_string(num) << " events" << endl;
	}
	void Del(int year, int month, int day, string s) {
		Date temp;
		try {
			temp = Date(year, month, day);
		}
		catch (exception & ex) {
			throw invalid_argument(ex.what());
			return;
		}
		
		int num = 0;
		num = db[temp].count(s);
		if (num == 0) {
			db[temp].erase(s);
			cout << "Event not found" << endl;
		}
		else {
			db[temp].erase(s);
			cout << "Deleted successfully" << endl;
		}
	}
	void Find(int year, int month, int day) {
		Date temp;
		try {
			temp = Date(year, month, day);
		}
		catch (exception & ex) {
			throw invalid_argument(ex.what());
			return;
		}
		for (const auto& i : db[temp]) {
			cout << i << endl;
		}
		if (db[temp].size() == 0) {
			db.erase(temp);
		}
	}
	void Print() {
		for (const auto& i : db) {
			for (const auto& it : i.second) {
				cout << setw(4) << setfill('0') << i.first.Year << '-' << setw(2) << setfill('0') << i.first.Month << '-' <<
				setw(2) << setfill('0') << i.first.Day << " " << it << endl;
			}
		}
	}
};
void Process(string temp, DateBase& db) {
	stringstream stream;
	stream << temp;
	string s;
	getline(stream, s, ' ');
	int year, month, day;
	if (s == "Add") {
		/*char a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + templine);
		}
		stream >> year;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> month;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + to_string(a) + templine);
		}
		stream.ignore(1);
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + '-' + to_string(month) + '-' + templine);
		}
		stream >> day;*/
		Date date;
		if (makedate1(stream, date)) {
			string s;
			stream >> s;
			db.Add(date.Year, date.Month, date.Day, s);
		}
	}
	else if (s == "Find") {
		/*char a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + templine);
		}
		stream >> year;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> month;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + to_string(a) + templine);
		}
		stream.ignore(1);
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + '-' + to_string(month) + '-' + templine);
		}*/
		Date date;
		if (makedate1(stream, date)) {
			stream >> day;
			db.Find(date.Year, date.Month, date.Day);
		}
	}
	else if (s == "Print") {
		db.Print();
	}
	else if (s == "Del") {
		/*char a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + templine);
		}
		stream >> year;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> a;
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + templine);
		}
		stream >> month;
		if (stream.peek() != '-') {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + to_string(a) + templine);
		}
		stream.ignore(1);
		if (!(isdigit(stream.peek()))) {
			string templine;
			getline(stream, templine, ' ');
			throw invalid_argument("Wrong date format: " + to_string(year) + '-' + to_string(month) + '-' + templine);
		}*/
		Date date;
		if (makedate1(stream, date)) {
			//stream >> day;
			if (stream.peek() != '\n' && stream.peek() != EOF) {
				stream >> s;
				if (s.size() != 0) {
					db.Del(date.Year, date.Month, date.Day, s);
				}
				else {
					db.Del(date.Year, date.Month, date.Day);
				}
			}
			else {
				db.Del(date.Year, date.Month, date.Day);
			}
		}
	}
	else if (s.size() != 0){
		throw invalid_argument("Unknown command: " + s);
	}
}
int main() {
	string temp;
	DateBase db;
	while (getline(cin, temp)) {
		try {
			Process(temp, db);
		}
		catch (exception & ex) {
			cout << ex.what();
			exit(0);
		}
	}
	return 0;
}