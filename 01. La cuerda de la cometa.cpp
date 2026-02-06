// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

struct tInfo {
    long long int longitud;
    long long int coste;
};

bool resuelveCaso() {
    long long int num_tipos; cin >> num_tipos;
    long long int suma; cin >> suma;

    if (!std::cin)
        return false;

    vector<tInfo> long_cuerdas(num_tipos);
    for (int i = 0; i < num_tipos; ++i) {
        cin >> long_cuerdas[i].longitud >> long_cuerdas[i].coste;
    }

    vector<vector<long long int>> matriz_formas(num_tipos + 1, vector<long long int>(suma + 1));
    for (int i = 0; i < num_tipos + 1; ++i) {
        matriz_formas[i][0] = 1;
    }
    for (int j = 1; j < suma + 1; ++j) {
        matriz_formas[0][j] = 0;
    }
    for (int i = 1; i < num_tipos + 1; ++i) {
        for (int j = 1; j < suma + 1; ++j) {
            if (long_cuerdas[i - 1].longitud > j) {
                matriz_formas[i][j] = matriz_formas[i - 1][j];
            }
            else {
                matriz_formas[i][j] = matriz_formas[i - 1][j] + matriz_formas[i - 1][j - long_cuerdas[i - 1].longitud];
            }
        }
    }
    
    vector<vector<long long int>> matriz_min_long(num_tipos + 1, vector<long long int>(suma + 1));
    for (int i = 0; i < num_tipos + 1; ++i) {
        matriz_min_long[i][0] = 0;
    }
    for (int j = 1; j < suma + 1; ++j) {
        matriz_min_long[0][j] = INT_MAX;
    }
    for (int i = 1; i < num_tipos + 1; ++i) {
        for (int j = 1; j < suma + 1; ++j) {
            if (long_cuerdas[i - 1].longitud > j) {
                matriz_min_long[i][j] = matriz_min_long[i - 1][j];
            }
            else {
                matriz_min_long[i][j] = min(matriz_min_long[i - 1][j], matriz_min_long[i - 1][j - long_cuerdas[i - 1].longitud] + 1);
            }
        }
    }

    vector<vector<long long int>> matriz_min_precio(num_tipos + 1, vector<long long int>(suma + 1));
    for (int i = 0; i < num_tipos + 1; ++i) {
        matriz_min_precio[i][0] = 0;
    }
    for (int j = 1; j < suma + 1; ++j) {
        matriz_min_precio[0][j] = INT_MAX;
    }
    for (int i = 1; i < num_tipos + 1; ++i) {
        for (int j = 1; j < suma + 1; ++j) {
            if (long_cuerdas[i - 1].longitud > j) {
                matriz_min_precio[i][j] = matriz_min_precio[i - 1][j];
            }
            else {
                matriz_min_precio[i][j] = min(matriz_min_precio[i - 1][j], matriz_min_precio[i - 1][j - long_cuerdas[i - 1].longitud] + long_cuerdas[i - 1].coste);
            }
        }
    }

    if (matriz_formas[num_tipos][suma] == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << matriz_formas[num_tipos][suma] << ' ' << matriz_min_long[num_tipos][suma] << ' ' << matriz_min_precio[num_tipos][suma] << '\n';
    }


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}