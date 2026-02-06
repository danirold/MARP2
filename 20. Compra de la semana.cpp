// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct tNodo {
    vector<int> sol;
    int k;
    int coste;
    int coste_opt; //Prioridad
    vector<int> asignado;

    bool operator< (tNodo const& t) const {
        return coste_opt > t.coste_opt;
    }
};

int coste_optimista(tNodo& y, vector<vector<int>> const& supers, int n, int m) {
    int min_costes_acum = 0;
    for (int i = n; i > y.k; --i) {
        int minimo = INT_MAX;
        for (int j = 1; j <= m; ++j) {
            if (y.asignado[j] < 3) {
                minimo = min(minimo, supers[i][j]);
            }
        }
        min_costes_acum += minimo;
    }
    return y.coste + min_costes_acum;
}

int coste_pesimista(tNodo& y, vector<vector<int>> const& supers, int n, int m) {
    int max_costes_acum = 0;
    for (int i = n; i > y.k; --i) {
        int maximo = 0;
        for (int j = 1; j <= m; ++j) {
            if (y.asignado[j] < 3) {
                maximo = max(maximo, supers[i][j]);
            }
        }
        max_costes_acum += maximo;
    }
    return y.coste + max_costes_acum;
}

void resolver(vector<vector<int>> const& supers, vector<int>& solMejor, int& costeMin, int n, int m) {
    priority_queue<tNodo> pq;  //Cola de prioridad de mínimos
    tNodo y;
    y.k = 0;
    vector<int> marcas(m + 1, 0);
    vector<int> sol(n + 1, 0);
    y.coste = 0;  //Generamos la raíz del árbol
    y.asignado = marcas;
    y.sol = sol;
    y.coste_opt = coste_optimista(y, supers, n, m);
    costeMin = coste_pesimista(y, supers, n, m);

    pq.push(y);

    while (!pq.empty() && pq.top().coste_opt <= costeMin) {
        y = pq.top(); pq.pop();
        //Generamos los hijos de y
        tNodo x;
        x.sol = y.sol;
        x.k = y.k + 1;
        x.asignado = y.asignado;
        for (int i = 1; i <= m; ++i) {
            if (x.asignado[i] < 3) {  //Si un hijo no es factible, es descartado
                x.sol[x.k] = i;
                x.asignado[i]++;
                x.coste = y.coste + supers[x.k][i];
                x.coste_opt = coste_optimista(x, supers, n, m);  //Actualizo el coste óptimo estimado
                if (x.coste_opt <= costeMin) {
                    if (x.k == n) {  //Es solución
                        solMejor = x.sol; costeMin = x.coste;
                    }
                    else {
                        pq.push(x);
                        costeMin = min(costeMin, coste_pesimista(x, supers, n, m));
                    }
                }
                x.asignado[i]--;
            }
        }
    }
}

void resuelveCaso() {
    int m; int n; 
    cin >> m >> n;

    vector<vector<int>> matriz(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) {
        matriz[i][0] = 0;
    }
    for (int i = 0; i <= m; ++i) {
        matriz[0][i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> matriz[j][i];
        }
    }

    vector<int> solMejor(n + 1, 0);
    int costeMin = INT_MAX;
    resolver(matriz, solMejor, costeMin, n, m);

    cout << costeMin << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
