// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct datos {
    bool a = false;
    bool b = false;
    bool c = false;
};

bool es_posible(const string& cadena, int tam) {
    vector<vector<datos>> posibilidades(tam, vector<datos>(tam));

    for (int i = 0; i < tam; i++) {
        if (cadena[i] == 'a') posibilidades[i][i].a = true;
        else if (cadena[i] == 'b') posibilidades[i][i].b = true;
        else posibilidades[i][i].c = true;
    }

    for (int len = 2; len <= tam; ++len) {
        for (int i = 0; i < tam - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                if (posibilidades[i][k].c && posibilidades[k + 1][j].a || posibilidades[i][k].b && posibilidades[k + 1][j].c || posibilidades[i][k].a && posibilidades[k + 1][j].c) {
                    posibilidades[i][j].a = true;
                }
                if (posibilidades[i][k].a && posibilidades[k + 1][j].a || posibilidades[i][k].a && posibilidades[k + 1][j].b || posibilidades[i][k].b && posibilidades[k + 1][j].b) {
                    posibilidades[i][j].b = true;
                }
                if (posibilidades[i][k].b && posibilidades[k + 1][j].a || posibilidades[i][k].c && posibilidades[k + 1][j].b || posibilidades[i][k].c && posibilidades[k + 1][j].c) {
                    posibilidades[i][j].c = true;
                }
            }
        }
    }
    return posibilidades[0][tam - 1].a;
}

bool resuelveCaso() {
    string cadena; cin >> cadena;

    if (!std::cin)
        return false;

    bool resultado = es_posible(cadena, cadena.size());
    if (resultado) cout << "SI\n";
    else cout << "NO\n";

    return true;
}

int main() {

    while (resuelveCaso());



    return 0;
}