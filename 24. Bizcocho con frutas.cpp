// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int resolver(vector<int> const& bizcocho, int n) {
	vector<vector<int>> matriz(n, vector<int>(n));
	for (int i = 0; i < n - 1; i++) {
		matriz[i][i + 1] = 0;
		if (bizcocho[i] == bizcocho[i + 1] && bizcocho[i] != 0) matriz[i][i + 1] = 1;
	}
	for (int d = 2; d <= n - 1; ++d) {
		for (int i = 0; i <= n - d - 1; ++i) {
			int j = i + d;
			int extremos = 0; int izq = 0; int dcha = 0;
			if (bizcocho[i] == bizcocho[j] && bizcocho[i] != 0) extremos = 1;
			if (bizcocho[i] == bizcocho[i + 1] && bizcocho[i] != 0) izq = 1;
			if (bizcocho[j - 1] == bizcocho[j] && bizcocho[j] != 0) dcha = 1;
			matriz[i][j] = max(matriz[i + 2][j] + izq, max(matriz[i + 1][j - 1] + extremos, matriz[i][j - 2] + dcha));
		}
	}
	return matriz[0][n - 1];
}

bool resuelveCaso() {
	int num_trozos; cin >> num_trozos;
	if (!cin) return false;

	vector<int> bizcocho(num_trozos);
	for (int i = 0; i < num_trozos; ++i) cin >> bizcocho[i];

	cout << resolver(bizcocho, num_trozos) << '\n';

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}