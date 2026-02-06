// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

bool resuelvecasos() {
	int n; cin >> n;

	if (!cin)
		return false;

	else {
		vector<vector<int>> matriz(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matriz[i][j];
			}
		}

		vector<vector<int>> sol(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			sol[0][i] = matriz[0][i];
		}
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j > 0 && j < n - 1) {
					sol[i][j] = max(sol[i][j], max(sol[i - 1][j - 1], max(sol[i - 1][j], sol[i - 1][j + 1]))) + matriz[i][j];
				}
				else if (j > 0) {
					sol[i][j] = max(sol[i][j], max(sol[i - 1][j - 1], sol[i - 1][j])) + matriz[i][j];
				}
				else if (j < n - 1) {
					sol[i][j] = max(sol[i][j], max(sol[i - 1][j + 1], sol[i - 1][j])) + matriz[i][j];
				}
			}
		}
		int fila_emp = -1, maxima_suma = INT_MIN;
		for (int i = 0; i < n; i++) {
			if (sol[n - 1][i] > maxima_suma) {
				maxima_suma = sol[n - 1][i];
				fila_emp = i;
			}
		}

		cout << maxima_suma << ' ' << fila_emp + 1 << '\n';

		return true;
	}
}

int main() {
	while (resuelvecasos());
	return 0;
}