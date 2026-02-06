// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct tInfo {
    int grupos;
    int precio;
};

int resolver(vector<tInfo> const& festivales, int i, int j, vector<vector<int>> & matriz) {
    if (matriz[i][j] != -1) return matriz[i][j]; //Subproblema ya resuelto
    if (i == 0 || j == 0) matriz[i][j] = 0;  //No quedan festivales disponibles o no queda dinero suficiente
    else if (festivales[i - 1].precio > j) {  //El precio del festival supera al presupuesto
        matriz[i][j] = resolver(festivales, i - 1, j, matriz);
    }
    else {
        matriz[i][j] = max(resolver(festivales, i - 1, j, matriz), resolver(festivales, i - 1, j - festivales[i - 1].precio, matriz) + festivales[i - 1].grupos);
    }
    return matriz[i][j];
}

bool resuelveCaso() {
    int presupuesto; cin >> presupuesto;

    if (!std::cin)
        return false;

    int num_grupos; cin >> num_grupos;
    vector<tInfo> festivales(num_grupos);
    for (int i = 0; i < num_grupos; ++i) {
        cin >> festivales[i].grupos >> festivales[i].precio;
    }

    vector<vector<int>> matriz(num_grupos + 1, vector<int>(presupuesto + 1, -1));

    int sol = resolver(festivales, num_grupos, presupuesto, matriz);
    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}