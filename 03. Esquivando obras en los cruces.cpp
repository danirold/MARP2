// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int filas, col; 
    cin >> filas >> col;

    if (!std::cin)
        return false;

    vector<vector<char>> matriz(filas, vector<char>(col));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> matriz[i][j];
        }
    }

    vector<vector<int>> formas(filas, vector<int>(col, 0));
    formas[filas - 1][col - 1] = 1;

    for (int i = filas - 1; i >= 0; --i) {
        for (int j = col - 1; j >= 0; --j) {
            if (matriz[i][j] == '.') {
                if (i + 1 < filas && j + 1 < col) {
                    if (matriz[i + 1][j] != 'X' && matriz[i][j + 1] != 'X') formas[i][j] += formas[i + 1][j] + formas[i][j + 1];
                    else if (matriz[i + 1][j] == 'X' && matriz[i][j + 1] != 'X') formas[i][j] += formas[i][j + 1];
                    else if (matriz[i + 1][j] != 'X' && matriz[i][j + 1] == 'X') formas[i][j] += formas[i + 1][j];
                }
                else if (i + 1 < filas && j + 1 >= col) {
                    if (matriz[i + 1][j] != 'X') formas[i][j] += formas[i + 1][j];
                }
                else if (i + 1 >= filas && j + 1 < col) {
                    if (matriz[i][j + 1] != 'X') formas[i][j] += formas[i][j + 1];
                }
            }
        }
    }

    cout << formas[0][0] << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}