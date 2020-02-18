#include <iostream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
using namespace std;

class Rational {
	long long int num, denum;
public:
	Rational() {
		num = 0;
		denum = 1;
	};
	Rational(int numerator, int denominator) {
		int a = abs(numerator), b = abs(denominator);
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");
		}
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		}
		if (numerator == 0) {
			num = 0;
			denum = 1;
		}
		else {
			int sign = 1;
			if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator > 0)) {
				sign = 1;
			}
			else {
				sign = -1;
			}
			num =  sign * abs(numerator) / (b + a);
			denum = abs(denominator) / (b + a);
		}
	}

	long long int Numerator() const {
		return num;
	}
	long long int Denominator() const {
		return denum;
	}
};
// Комментарии, которые говорят, что именно нужно реализовать в этой программе
Rational operator+(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}
Rational operator/(const Rational & lhs, const Rational & rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}
bool operator==(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator() || lhs.Denominator() == rhs.Denominator());
}
istream& operator>>(istream& stream, Rational& rational) {
	if (stream.peek() == EOF) return stream;
	int numerator, denominator;
	char c = ' ';
	stream >> numerator >> c >> denominator;
	if (c == '/') {
		Rational r(numerator, denominator);
		rational = r;
	}
	return stream;
}
istringstream& operator>>(istringstream& stream, Rational& rational) {
	if (stream.peek() == EOF) return stream;
	int numerator, denominator;
	char c = ' ';
	stream >> numerator >> c >> denominator;
	if (c == '/') {
		Rational r(numerator, denominator);
		rational = r;
	}
	return stream;
}
ostream& operator<<(ostream& stream, const Rational& rational) {
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}
ostringstream& operator<<(ostringstream& stream, const Rational& rational) {
	stream << rational.Numerator();
	stream << "/";
	stream << rational.Denominator();
	return stream;
}
bool operator<(const Rational& lhs, const Rational& rhs) {
	return (double(lhs.Numerator())/lhs.Denominator() < double(rhs.Numerator()) / rhs.Denominator());
}

Rational readNums() {
	int a, b;
	Rational lhs, rhs;
	std::cin >> a;
	if (std::cin.peek() != '/') {
		throw invalid_argument("Invalid argument");
	}
	std::cin.ignore(1);
	std::cin >> b;
	lhs =  Rational(a, b);
	char op;
	std::cin >> op;
	std::cin >> a;
	if (std::cin.peek() != '/') {
		throw invalid_argument("Invalid argument");
	}
	std::cin.ignore(1);
	std::cin >> b;
	rhs = Rational(a, b);
	if (op == '+') {
		return lhs + rhs;
	}
	if (op == '*') {
		return lhs * rhs;
	}
	if (op == '/') {
		return lhs / rhs;
	}
	if (op == '-') {
		return lhs - rhs;
	}
}
/*int main() {
	Rational r;
	try {
		r = readNums();
	}
	catch(exception& ex){
		cout << ex.what();
		return 0;
	}

	cout << r << endl;
	return 0;
}*/