// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int tam; cin >> tam;
    
    if (tam == 0)
        return false;

    vector<int> cantidades(tam);
    for (int i = 0; i < tam; ++i) {
        cin >> cantidades[i];
    }

    vector<vector<int>> matriz(tam, vector<int>(tam, -1));

    for (int i = 0; i < tam; ++i) {
        matriz[i][i] = cantidades[i];
    }
    int j = 1; int i = 0;
    while (j < tam) {
        matriz[i][j] = max(cantidades[i], cantidades[j]);
        ++i; ++j;
    }

    j = 2;
    while (j < tam) {
        int k = j; 
        int l = 0;
        while (l + 2 < tam && k < tam) {
            if (cantidades[k - 1] > cantidades[l] && cantidades[l + 1] > cantidades[k]) {
                matriz[l][k] = max(cantidades[k] + matriz[l][k - 2], cantidades[l] + matriz[l + 2][k]);
            }
            else if (cantidades[k - 1] > cantidades[l] && cantidades[l + 1] <= cantidades[k]) {
                matriz[l][k] = max(cantidades[k] + matriz[l][k - 2], cantidades[l] + matriz[l + 1][k - 1]);
            }
            else if (cantidades[k - 1] <= cantidades[l] && cantidades[l + 1] > cantidades[k]) {
                matriz[l][k] = max(cantidades[k] + matriz[l + 1][k - 1], cantidades[l] + matriz[l + 2][k]);
            }
            else {
                matriz[l][k] = max(cantidades[k] + matriz[l + 1][k - 1], cantidades[l] + matriz[l + 1][k - 1]);
            }
            ++k; ++l;
        }
        ++j;
    }

    cout << matriz[0][tam - 1] << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
