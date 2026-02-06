// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int resolver(string const& s) {
    int tam = s.size();
    vector<vector<int>> cantidad_min(tam, vector<int>(tam, 1000000000));

    for (int i = 0; i < tam; i++) cantidad_min[i][i] = 1;

    for (int len = 2; len <= tam; ++len) {
        for (int i = 0; i < tam - len + 1; ++i) {
            int j = i + len - 1;
            if (j - i == 1) {
                if (s[j] == s[i]) cantidad_min[i][j] = 1;
                else cantidad_min[i][j] = 2;
            }
            else {
                if (s[j] == s[j - 1] || s[i] == s[i + 1] || s[i] == s[j]) {
                    if (s[j] == s[j - 1]) cantidad_min[i][j] = min(cantidad_min[i][j], cantidad_min[i][j - 1]);
                    if (s[i] == s[i + 1]) cantidad_min[i][j] = min(cantidad_min[i][j], cantidad_min[i + 1][j]);
                    if (s[i] == s[j]) cantidad_min[i][j] = min(cantidad_min[i][j], cantidad_min[i + 1][j - 1] + 1);

                }
                else cantidad_min[i][j] = min(cantidad_min[i][j - 1], cantidad_min[i + 1][j]) + 1;
            }
        }
    }

    return cantidad_min[0][tam - 1];
}

bool resuelveCaso() {
    string palabra; cin >> palabra;

    if (!std::cin)
        return false;

    int sol = resolver(palabra);
    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}