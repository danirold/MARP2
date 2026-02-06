// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

void resuelveCaso() {
    int caras; cin >> caras;
    int suma; cin >> suma;

    vector<int> dado(caras, 0);
    for (int i = 0; i < caras; ++i) {
        dado[i] = i + 1;
    }

    vector<int> formas(suma + 1, 0); formas[0] = 1;
    for (int i = 0; i < caras; ++i) {
        for (int j = dado[i]; j <= suma; ++j) {
            formas[j] = formas[j] + formas[j - dado[i]];
        }
    }

    int formas_sol = formas[suma];
    cout << formas_sol << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
