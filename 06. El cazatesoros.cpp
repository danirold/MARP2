// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <deque>

using namespace std;

struct tCofre {
    int oro;
    int profund;
};

bool resuelveCaso() {
    int debajo_agua; cin >> debajo_agua;
    int num_cofres; cin >> num_cofres;

    if (!std::cin)
        return false;

    vector<tCofre> infor(num_cofres);
    for (int i = 0; i < num_cofres; ++i) {
        cin >> infor[i].profund >> infor[i].oro;
    }

    vector<vector<int>> matriz(num_cofres + 1, vector<int>(debajo_agua + 1, 0));

    for (int i = 1; i <= num_cofres; ++i) {
        for (int j = 1; j <= debajo_agua; ++j) {
            if (infor[i - 1].profund + 2 * infor[i - 1].profund > j) {
                matriz[i][j] = matriz[i - 1][j];
            }
            else {
                matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - infor[i - 1].profund - 2 * infor[i - 1].profund] + infor[i - 1].oro);
            }
        }
    }

    vector<bool> cuales(debajo_agua + 1, false);
    int resto = debajo_agua;
    int cofres_hallados = 0;
    deque<tCofre> lista_sol;

    for (int i = num_cofres; i >= 1; --i) {
        if (matriz[i][resto] == matriz[i-1][resto]) {
            // no cogemos objeto i
            cuales[i] = false;
        }
        else { // sí cogemos objeto i
            cuales[i] = true;
            cofres_hallados++;
            resto = resto - infor[i - 1].profund - 2 * infor[i - 1].profund;
            lista_sol.push_front({ infor[i - 1].oro, infor[i - 1].profund });
        }
    }

    cout << matriz[num_cofres][debajo_agua] << '\n' << cofres_hallados << '\n';
    int tam = lista_sol.size();
    for (int i = 0; i < tam; ++i) {
        cout << lista_sol.front().profund << ' ' << lista_sol.front().oro << '\n';
        lista_sol.pop_front();
    }

    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}