// Matr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>
using namespace std;
class Matrix {
	int rows;
	int cols;
	vector<int> v;
public:
	Matrix() {
		rows = 0;
		cols = 0;
		v.resize(0);
	}
	Matrix(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("out_of_range");
		}
		rows = num_rows;
		cols = num_cols;
		v.resize(rows * cols);
	}
	void Reset(int num_rows = 0, int num_cols = 0) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("out_of_range");
		}
		rows = num_rows;
		cols = num_cols;
		v.resize(rows * cols);
		for (auto& i : v) {
			i = 0;
		}
	}
	int At(int num_rows = 0, int num_cols = 0) const {
		if (num_rows >= rows || num_cols >= cols) {
			throw out_of_range("out_of_range");
		}
		return v[num_rows * cols + num_cols];
	}
	int& At(int num_rows = 0, int num_cols = 0) {
		if (num_rows >= rows || num_cols >= cols) {
			throw out_of_range("out_of_range");
		}
		int& res = v[num_rows * cols + num_cols];
		return res;
	}
	int GetNumRows() const {
		return rows;
	}
	int GetNumCols() const {
		return cols;
	}
};

istream& operator>>(istream& stream, Matrix& matrix) {
	if (stream.peek() == EOF) return stream;
	int rows, cols;
	stream >> rows >> cols;
	for (int i = 0; i < rows * cols; i++) {
		int& at = matrix.At(i / cols, i % cols);
		stream >> at;
	}
	return stream;
}
ostream& operator<<(ostream& stream, const Matrix& matrix) {
	//if (stream.peek() == EOF) return stream;
	int rows, cols;
	rows = matrix.GetNumRows();
	cols = matrix.GetNumCols();
	stream << rows << ' ' << cols;
	for (int i = 0; i < rows * cols; i++) {
		stream << ' ';
		int at = matrix.At(i / cols, i % cols);
		stream << at;
	}
	return stream;
}
bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumCols() == rhs.GetNumCols() && lhs.GetNumRows() == rhs.GetNumRows()) {
		int cols = lhs.GetNumCols();
		int rows = lhs.GetNumRows();
		for (int i = 0; i < cols * rows; i++) {
			if (lhs.At(i / cols, i % cols) != rhs.At(i / cols, i % cols)) {
				return false;
			}
		}
		return true;
	}
	return false;
}
Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumCols() == rhs.GetNumCols() && lhs.GetNumRows() == rhs.GetNumRows()) {
		int cols = lhs.GetNumCols();
		int rows = lhs.GetNumRows();
		Matrix m(rows, cols);
		for (int i = 0; i < rows * cols; i++) {
			m.At(i / cols, i % cols) = lhs.At(i / cols, i % cols) + rhs.At(i / cols, i % cols);
		}
		return m;
	}
	throw invalid_argument("invalid");
}
int main()
{
	/*Matrix one(2, 2);
	Matrix two(2, 2);

	cin >> one >> two;
	cout << one + two << endl;
	return 0;*/
	uint32_t x = -1;
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
