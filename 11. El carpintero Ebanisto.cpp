// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int calc_esfuerzo(int long_tablon, const vector<int>& cortes, int corte_ini, int corte_fin) {
    int ini = 0;
    if (corte_ini != 0) ini = cortes[corte_ini - 1];
    int fin = long_tablon;
    if (corte_fin != cortes.size() - 1) fin = cortes[corte_fin + 1];
    return 2 * (fin - ini);
}


bool resuelveCaso() {
    int long_tablon, num_cortes;
    cin >> long_tablon >> num_cortes;

    if (long_tablon == 0 && num_cortes == 0)
        return false;

    vector<int> cortes(num_cortes);
    for (int i = 0; i < num_cortes; ++i) {
        cin >> cortes[i];
    }

    vector<vector<int>> matriz(num_cortes, vector<int>(num_cortes, INT_MAX));

    for (int i = 0; i < num_cortes; i++)
        matriz[i][i] = calc_esfuerzo(long_tablon, cortes, i, i);


    for (int d = 1; d < num_cortes; d++) {
        for (int i = 0; i < num_cortes - d; i++) {
            int j = i + d; 
            int esfuerzo = calc_esfuerzo(long_tablon, cortes, i, j);

            for (int k = i + 1; k < j; k++) {
                int temp = matriz[i][k - 1] + matriz[k + 1][j] + esfuerzo;
                if (temp < matriz[i][j]) 
                    matriz[i][j] = temp;
            }
            
            matriz[i][j] = min(matriz[i][j], matriz[i][j - 1] + esfuerzo);
            matriz[i][j] = min(matriz[i][j], matriz[i + 1][j] + esfuerzo);
        }
    }

    cout << matriz[0][num_cortes - 1] << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
