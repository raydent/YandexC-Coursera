#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <deque>
using namespace std;

enum OP_CODES{plus = 1, minus = 2, muldiv = 100, mul = 101};
/*void building(deque<string>& equation, string op, int num) {
	equation.push_back(") ");
	equation.push_front("(");
	equation.push_back(op + " ");
	equation.push_back(to_string(num));
}*/
void building(deque<string>& equation, OP_CODES op, OP_CODES prev_op, int num) {
	if (op > prev_op + 1) {
		equation.push_back(")");
		equation.push_front("(");
	}
	equation.push_back(" ");
	string s;
	switch (op) {
	case(OP_CODES::plus):
		s = "+";
		break;
	case(OP_CODES::minus):
		s = "-";
		break;
	case(OP_CODES::mul):
		s = "*";
		break;
	case(OP_CODES::muldiv):
		s = "/";
		break;
	}
	equation.push_back(s + " ");
	equation.push_back(to_string(num));
}
int main() {
	int x, N;
	cin >> x >> N;
	char op;
	int num;
	deque <string> equation;
	equation.push_back(to_string(x));
	OP_CODES op_code = OP_CODES::plus;
	OP_CODES prev_op_code = OP_CODES::mul;
	string s(" ");
	while (N > 0) {
		N--;
		cin >> op >> num;
		switch (op) {
		case('+'):
			op_code = OP_CODES::plus;
			break;
		case('-'):
			op_code = OP_CODES::minus;
			break;
		case('/'):
			op_code = OP_CODES::muldiv;
			break;
		case('*'):
			op_code = OP_CODES::mul;
			break;
		default:
			op_code = OP_CODES::plus;
			break;
		}
		building(equation, op_code, prev_op_code, num);
		prev_op_code = op_code;
	}
	for (const auto& i : equation) {
		cout << i;
	}
	cout << endl;
}