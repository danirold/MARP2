#include <iostream>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"

using namespace std;

struct info {
	int numM;
	int formas;
};

void formas_minimas(const vector<int>& monedas, vector<info>& V, int N, int C) {
	for (int i = 1; i <= N; i++) {
		for (int j = C; j > 0; j--) {
			info nuevo = { EntInf::_intInf , 0 };
			int pos = j, k = 0;
			while (pos >= 0) {
				if (V[pos].numM + k < nuevo.numM) {
					nuevo.numM = V[pos].numM + k;
					nuevo.formas = V[pos].formas;
				}
				else if (V[pos].numM + k == nuevo.numM) {
					nuevo.formas += V[pos].formas;
				}
				k++;
				pos -= monedas[i - 1];
			}
			V[j] = nuevo;
		}
	}
}

bool resCaso() {
	int C, N; cin >> C;
	if (!cin) return false;
	cin >> N;

	vector<int> monedas(N);

	for (int& x : monedas)
		cin >> x;

	vector<info> V(C + 1, { EntInf::_intInf, 0 });
	V[0] = { 0,1 };

	formas_minimas(monedas, V, N, C);

	cout << V[C].formas << "\n";

	return true;
}


int main() {
	while (resCaso()) {}
	return 0;
}