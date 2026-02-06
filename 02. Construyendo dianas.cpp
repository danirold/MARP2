// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

bool resuelveCaso() {
    int suma; int num_dianas;
    cin >> suma >> num_dianas;

    if (!std::cin)
        return false;

    vector<int> dianas(num_dianas);
    for (int i = 0; i < num_dianas; ++i) cin >> dianas[i];

    vector<int> min_long(suma + 1, INT_MAX - 2);
    min_long[0] = 0;
    for (int i = 1; i <= num_dianas; ++i) {
        for (int j = dianas[i - 1]; j <= suma; ++j) {
            min_long[j] = min(min_long[j], min_long[j - dianas[i - 1]] + 1);
        }
    }
    int minima_long = min_long[suma];

    if (minima_long == INT_MAX - 2) cout << "Imposible\n";
    else {
        cout << minima_long << ": ";

        vector<int> cuantas(minima_long, 0);
        int i = num_dianas - 1; int j = suma; int ind = 0;
        while (j > 0 && ind < minima_long) { 
            if (j - dianas[i] >= 0 && min_long[j] == min_long[j - dianas[i]] + 1) {
                cuantas[ind] = dianas[i];
                ind++;
                j = j - dianas[i];
            }
            else 
                --i;
        }

        for (int i = 0; i < cuantas.size(); ++i) {
            cout << cuantas[i] << ' ';
        }
        cout << '\n';

    }


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}