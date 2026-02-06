// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct tCancion {
	float duracion;
	float valor;
};

bool operator <(tCancion const& c1, tCancion const& c2) {
	return (c1.valor / c1.duracion) < (c2.valor / c2.duracion);
}

bool operator >(tCancion const& c1, tCancion const& c2) {
	return (c1.valor / c1.duracion) > (c2.valor / c2.duracion);
}

struct nodo {
	int indice;
	float puntuacion;
	float puntuacionOptimista;
	float ocupadoCara1;
	float ocupadoCara2;
};

bool operator >(nodo const& n1, nodo const& n2) {
	return n1.puntuacionOptimista > n2.puntuacionOptimista;
}

bool operator <(nodo const& n1, nodo const& n2) {
	return n1.puntuacionOptimista < n2.puntuacionOptimista;
}

float optimista(vector<tCancion> const& canciones, float T, int indice, float puntuacion, float ocupadoCara1, float ocupadoCara2, int n) {
	float opt = puntuacion;
	float hueco = 2 * T - (ocupadoCara1 + ocupadoCara2);
	int j = indice + 1;
	while (j <= n && canciones[j].duracion <= hueco) {
		hueco -= canciones[j].duracion;
		opt += canciones[j].valor;
		j++;
	}
	if (j <= n) {
		opt += (hueco / canciones[j].duracion) * canciones[j].valor;
	}
	return opt;
}

float pesimista(vector<tCancion> const& canciones, float T, int indice, float puntuacion, float ocupadoCara1, float ocupadoCara2, int n) {
	float ocupadoCara1Aux = ocupadoCara1;
	float ocupadoCara2Aux = ocupadoCara2;
	float pes = puntuacion;
	int j = indice + 1;
	while (j <= n && (ocupadoCara1Aux <= T || ocupadoCara2Aux <= T)) {
		if (ocupadoCara1Aux + canciones[j].duracion <= T) {
			ocupadoCara1Aux += canciones[j].duracion;
			pes += canciones[j].valor;
		}
		else if (ocupadoCara2Aux + canciones[j].duracion <= T) {
			ocupadoCara2Aux += canciones[j].duracion;
			pes += canciones[j].valor;
		}
		j++;
	}
	return pes;
}



bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)
		return false;
	float T;
	cin >> T;
	vector<tCancion> canciones(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> canciones[i].duracion >> canciones[i].valor;

	sort(canciones.begin() + 1, canciones.end(), greater<tCancion>());

	nodo X, Y; priority_queue<nodo> C;
	Y.indice = 0; Y.puntuacion = 0; Y.ocupadoCara1 = 0; Y.ocupadoCara2 = 0;
	Y.puntuacionOptimista = optimista(canciones, T, Y.indice, Y.puntuacion, Y.ocupadoCara1, Y.ocupadoCara2, n);
	C.push(Y);
	float mejor = pesimista(canciones, T, Y.indice, Y.puntuacion, Y.ocupadoCara1, Y.ocupadoCara2, n);
	while (!C.empty() && C.top().puntuacionOptimista >= mejor) {
		Y = C.top(); C.pop();
		X.indice = Y.indice + 1;

		if (Y.ocupadoCara1 + canciones[X.indice].duracion <= T) {
			X.puntuacion = Y.puntuacion + canciones[X.indice].valor;
			X.ocupadoCara1 = Y.ocupadoCara1 + canciones[X.indice].duracion;
			X.ocupadoCara2 = Y.ocupadoCara2;
			X.puntuacionOptimista = Y.puntuacionOptimista;
			if (X.indice == n) mejor = X.puntuacion;
			else C.push(X);
		}

		if (Y.ocupadoCara1 != Y.ocupadoCara2 && Y.ocupadoCara2 + canciones[X.indice].duracion <= T) {
			X.puntuacion = Y.puntuacion + canciones[X.indice].valor;
			X.ocupadoCara1 = Y.ocupadoCara1;
			X.ocupadoCara2 = Y.ocupadoCara2 + canciones[X.indice].duracion;
			X.puntuacionOptimista = Y.puntuacionOptimista;
			if (X.indice == n) mejor = X.puntuacion;
			else {
				C.push(X);
				mejor = max(mejor, pesimista(canciones, T, X.indice, X.puntuacion, X.ocupadoCara1, X.ocupadoCara2, n));
			}
		}
		X.ocupadoCara1 = Y.ocupadoCara1;
		X.ocupadoCara2 = Y.ocupadoCara2;
		X.puntuacion = Y.puntuacion;
		X.puntuacionOptimista = optimista(canciones, T, X.indice, X.puntuacion, X.ocupadoCara1, X.ocupadoCara2, n);
		if (X.puntuacionOptimista >= mejor) {
			if (X.indice == n) mejor = X.puntuacion;
			else {
				C.push(X);
				mejor = max(mejor, pesimista(canciones, T, X.indice, X.puntuacion, X.ocupadoCara1, X.ocupadoCara2, n));
			}
		}
	}
	cout << mejor << '\n';
	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}