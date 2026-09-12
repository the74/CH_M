#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	ifstream fin("matr.txt");
	if (!fin.is_open()) {
		cerr << "Oшибка: не удалось открыть файл" << endl;
		return 1;
	}

	int n;
	fin >> n;

	vector<vector<double>> a(n, vector<double>(n));
	vector<double> b(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		fin >> b[i];
	}
	fin.close();

	cout << "Исходная матрица A и вектор b:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "| " << b[i] << "\n";
	}
	cout << "\n";

	for (int k = 0; k < n - 1; k++) {

		if (a[k][k] == 0) {
			cerr << "Ошибка: нулевой ведущий элемент a[" << k << "][" << k << "]" << endl;
			return 1;
		}

		for (int i = k + 1; i < n; i++) {

			double t_ik = a[i][k] / a[k][k];

			b[i] = b[i] - t_ik * b[k];

			for (int j = k + 1; j < n; j++) {
				a[i][j] = a[i][j] - t_ik * a[k][j];
			}

			a[i][k] = 0;
		}
	}

	cout << "Ступенчатая матрица:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "| " << b[i] << "\n";
	}
	cout << "\n";

	vector<double> x(n);

	if (a[n - 1][n - 1] == 0.0) {
		cerr << "Ошибка: деление на ноль при обратном ходе" << endl;
		return 1;
	}
	x[n - 1] = b[n - 1] / a[n - 1][n - 1];

	for (int k = n - 2; k >= 0; k--) {
		double sum = b[k];

		for (int j = k + 1; j < n; j++) {
			sum -= a[k][j] * x[j];
		}

		if (a[k][k] == 0.0) {
			cerr << "Ошибка: деление на ноль при обратном ходе" << endl;
			return 1;
		}
		x[k] = sum / a[k][k];
	}

	cout << "Решение системы:\n";
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << x[i] << "\n";
	}

	system("pause");

}