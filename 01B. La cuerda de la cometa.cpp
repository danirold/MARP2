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
    
    
    vector<long long int> formas(suma + 1, 0); 
    formas[0] = 1;
    for (int i = 1; i <= num_tipos; ++i) {
        for (int j = suma; j >= long_cuerdas[i - 1].longitud; --j) {
            formas[j] += formas[j - long_cuerdas[i - 1].longitud];
        }
    }
    long long int num_formas = formas[suma];

    vector<long long int> min_long(suma + 1, INT_MAX - 2);
    min_long[0] = 0;
    for (long long int i = 1; i <= num_tipos; ++i) {
        for (long long int j = suma; j >= long_cuerdas[i - 1].longitud; --j) {
            min_long[j] = min(min_long[j], min_long[j - long_cuerdas[i - 1].longitud] + 1);
        }
    }
    long long int minima_long = min_long[suma];

    vector<long long int> min_precio(suma + 1, INT_MAX - 2);
    min_precio[0] = 0;
    for (long long int i = 1; i <= num_tipos; ++i) {
        for (long long int j = suma; j >= long_cuerdas[i - 1].longitud; --j) {
            min_precio[j] = min(min_precio[j], min_precio[j - long_cuerdas[i - 1].longitud] + long_cuerdas[i - 1].coste);
        }
    }
    long long int minimo_coste = min_precio[suma];

    if (num_formas == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << num_formas << ' ' << minima_long << ' ' << minimo_coste << '\n';
    }


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}