// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int n, m; cin >> n >> m;

    if (!std::cin)
        return false;

    vector<vector<int>> matriz(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matriz[i][j];
        }
    }

    vector<vector<int>> formas(n, vector<int>(m, 0));
    formas[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + matriz[i][j] < n) {
                formas[i + matriz[i][j]][j] += formas[i][j];
            }
            if (j + matriz[i][j] < m) {
                formas[i][j + matriz[i][j]] += formas[i][j];
            }
        }
    }

    cout << formas[n - 1][m - 1] << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}