// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct tInfo {
    int cantidad;
    int valor;
};

struct tSol {
    bool hay_sol;
    int sol;
};

tSol resolver(vector<tInfo> & monedas, int const& precio) {
    vector<vector<int>> matriz(monedas.size() + 1, vector<int>(precio + 1, 50000000));
    matriz[0][0] = 0;
    for (int i = 1; i <= monedas.size(); ++i) {
        matriz[i][0] = 0;
        for (int j = 1; j <= precio; ++j) {
            if (monedas[i - 1].valor > j) {
                matriz[i][j] = matriz[i - 1][j];
            }
            else {
                matriz[i][j] = matriz[i - 1][j];
                for (int k = 1; k <= min(monedas[i - 1].cantidad, j/monedas[i -1].valor); ++k) {
                    matriz[i][j] = min(matriz[i][j], matriz[i- 1][j - k * monedas[i - 1].valor] + k);
                }
            }
        }
    }
    if (matriz[monedas.size()][precio] == 50000000) {
        return { false, 0 };
    }
    else {
        return { true, matriz[monedas.size()][precio] };
    }
}

bool resuelveCaso() {
    int tipos; cin >> tipos;

    if (!std::cin)
        return false;

    vector<tInfo> monedas(tipos);
    int cantidad, valor;
    for (int i = 0; i < tipos; ++i) {
        cin >> valor;
        monedas[i].valor = valor;
    }
    for (int i = 0; i < tipos; ++i) {
        cin >> cantidad;
        monedas[i].cantidad = cantidad;
    }

    int precio; cin >> precio;

    tSol sol = resolver(monedas, precio);
    if (sol.hay_sol) {
        cout << "SI " << sol.sol << '\n';
    }
    else cout << "NO\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}