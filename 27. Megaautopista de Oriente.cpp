// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool resuelveCaso() {
    int num_areas; cin >> num_areas;
    int kil_sep; cin >> kil_sep;

    if (!std::cin)
        return false;

    vector<int> area_desc(num_areas);
    vector<int> beneficios(num_areas);
    for (int i = 0; i < num_areas; ++i) {
        cin >> area_desc[i];
    }
    for (int i = 0; i < num_areas; ++i) {
        cin >> beneficios[i];
    }

    vector<int> anterior(num_areas, -1);
    int aux = -1;
    for (int i = 1; i < num_areas; i++) {
        while ((area_desc[i] - area_desc[aux + 1]) >= kil_sep)aux++;
        anterior[i] = aux;
    }
    vector<int> v(num_areas + 1, 0);
    v[0] = 0;
    for (int i = 0; i < num_areas; i++) {
        v[i + 1] = max(v[anterior[i] + 1] + beneficios[i], v[i]);
    }
    cout << v[num_areas] << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}