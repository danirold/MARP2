// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

int suma(int n1, int n2) {
    if (n1 == INT_MAX || n2 == INT_MAX || n1 >= (INT_MAX - n2)) return INT_MAX;
    else return n1 + n2;
}

struct nodo {
    int indice;
    int costeActual;
    int costeOptimista;
    int numFacultades;
    int numMascarillas;
    vector<int> facultades;
};

bool operator<(nodo const& n1, nodo const& n2) {
    if (n1.costeOptimista > n2.costeOptimista) return true;
    else return false;
}

int cotaOptimista(vector<pair<int, int>> suministradores, int numUniversidades, int numSuministradores, int total, nodo X) {
    int optimista = X.costeActual;
    int restantes = total - X.numMascarillas;
    for (int i = X.indice + 1; i < numSuministradores && restantes > 0; i++) {
        int masc = min(suministradores[i].first, restantes);
        int costeMascarillas = suma(0, masc * suministradores[i].second);
        optimista = suma(optimista, costeMascarillas);
        restantes -= masc;
    }
    if (restantes > 0) optimista = INT_MAX;
    return optimista;
}

void resolver(vector<int> facultades, vector<pair<int, int>> suministradores, int numUniversidades, int numSuministradores, int total) {
    nodo X, Y;
    priority_queue<nodo> C;
    Y.indice = -1;
    Y.costeActual = 0;
    Y.facultades = facultades;
    Y.numMascarillas = 0;
    Y.numFacultades = 0;
    for (int i = 0; i < numUniversidades; i++) {
        if (facultades[i] == 0) {
            Y.numFacultades++;
        }
    }
    Y.costeOptimista = cotaOptimista(suministradores, numUniversidades, numSuministradores, total, Y);
    C.push(Y);
    int costeOptimista = INT_MAX;
    while (!C.empty() && C.top().costeOptimista <= costeOptimista) {
        Y = C.top(); C.pop();
        X.indice = Y.indice + 1;
        X.facultades = Y.facultades;
        X.numMascarillas = Y.numMascarillas;
        X.numFacultades = Y.numFacultades;
        for (int t = 0; t < numUniversidades; ++t) {
            if (X.facultades[t] > 0) {
                X = Y; X.indice++;
                int masc = min(suministradores[X.indice].first, X.facultades[t]);
                X.facultades[t] -= masc;
                int costeMascarillas = suma(0, masc * suministradores[X.indice].second);
                X.costeActual = X.costeActual + costeMascarillas;
                X.numMascarillas += masc;
                if (X.facultades[t] == 0) ++X.numFacultades;
                X.costeOptimista = cotaOptimista(suministradores, numUniversidades, numSuministradores, total, X);
                if (X.costeOptimista <= costeOptimista) {
                    if (X.indice == numSuministradores - 1 || X.numMascarillas == total) {
                        if ((X.numFacultades == numUniversidades && (X.costeActual <= costeOptimista))) costeOptimista = X.costeActual;
                    }
                    else C.push(X);
                }
            }
        }
    }
    if (costeOptimista < INT_MAX) cout << costeOptimista << '\n';
    else cout << "NO";
}

void resuelveCaso() {
    int numUniversidades, numSuministradores, total;
    total = 0;
    cin >> numUniversidades >> numSuministradores;
    vector<int> facultades(numUniversidades);
    for (int i = 0; i < numUniversidades; i++) {
        cin >> facultades[i];
        total += facultades[i];
    }
    vector<pair<int, int>> suministradores(numSuministradores);
    for (int i = 0; i < numSuministradores; i++) cin >> suministradores[i].first;
    for (int i = 0; i < numSuministradores; i++) cin >> suministradores[i].second;
    resolver(facultades, suministradores, numUniversidades, numSuministradores, total);
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
