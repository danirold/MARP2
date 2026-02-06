// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int num_pivotes, piv_pasar;
    cin >> num_pivotes >> piv_pasar;

    if (num_pivotes == 0 && piv_pasar == 0)
        return false;

	vector<int> v(num_pivotes, 0);
	v[0] = 1;
	int pivoteactual = 1;
	for (int i = 1; i < num_pivotes; i++) {
		for (int j = 0; j <= piv_pasar; j++) {
			if (i - 1 - j >= 0) {
				v[i] += v[i - 1 - j];
				if (v[i] > 1000000007)
					v[i] = v[i] % 1000000007;
			}
		}
	}
	cout << v[num_pivotes - 1] % 1000000007 << '\n';


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
