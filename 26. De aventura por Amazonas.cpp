// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

void floyd(vector<vector<int>> const& matriz_ady, vector<vector<int>>& C) {
    int n = matriz_ady.size() - 1;
    // inicialización
    C = matriz_ady;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                int temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {
    int num_pueblos; cin >> num_pueblos;

    if (!std::cin)
        return false;

    vector<vector<int>> matriz_ady(num_pueblos + 1, vector<int>(num_pueblos + 1, 100000000));
    for (int i = 1; i < num_pueblos + 1; ++i) {
        matriz_ady[i][i] = 0;
    }

    for (int i = 1; i < num_pueblos; ++i) {
        int j = i + 1; int coste;
        while (j < num_pueblos + 1) {
            cin >> coste;
            matriz_ady[i][j] = coste;
            ++j;
        }
    }

    vector<vector<int>> C(0, vector<int>(0));

    floyd(matriz_ady, C);
    for (int i = 1; i < num_pueblos; ++i) {
        int j = i + 1; int coste;
        while (j < num_pueblos + 1) {
            cout << C[i][j] << ' ';
            ++j;
        }
        cout << '\n';
    }


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}