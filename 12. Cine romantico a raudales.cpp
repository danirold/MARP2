// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int DESCANSO = 10;

struct tPeli {
    int ini; int durac;
};
bool operator<(tPeli const& p1, tPeli const& p2) {
    return p1.ini < p2.ini;
}

int resolver(vector<tPeli> pelis) {
    vector<int> cines(24*60 + DESCANSO + 1, 0);
    for (auto peli : pelis) {
        for (int j = peli.ini + peli.durac + DESCANSO; j < 24 * 60 + DESCANSO + 1; ++j) {
            cines[j] = max(cines[j], cines[peli.ini] + peli.durac);
        }
    }
    return cines.back();
}

bool resuelveCaso() {
    int num_pelis; cin >> num_pelis;

    if (num_pelis == 0)
        return false;

    vector<tPeli> pelis(num_pelis);
    for (int i = 0; i < num_pelis; ++i) {
        int h; char c; int m; int d;
        cin >> h >> c >> m >> d;
        pelis[i] = { h * 60 + m, d};
    }
    sort(pelis.begin(), pelis.end());


    int sol = resolver(pelis);

    cout << sol << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
