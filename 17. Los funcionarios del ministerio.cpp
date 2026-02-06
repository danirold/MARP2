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
    int tiempo;
    int tiempo_opt; //Prioridad
    vector<bool> asignado;

    bool operator< (tNodo const& t) const {
        return tiempo_opt > t.tiempo_opt;
    }
};

int coste_optimista(tNodo& y, vector<vector<int>> const& tiempos, int n) {
    int min_tiempos_acum = 0;
    for (int i = n; i > y.k; --i) {
        int minimo = INT_MAX;
        for (int j = 1; j <= n; ++j) {
            if (!y.asignado[j]) {
                minimo = min(minimo, tiempos[i][j]);
            }
        }
        min_tiempos_acum += minimo;
    }
    return y.tiempo + min_tiempos_acum;
}

int coste_pesimista(tNodo& y, vector<vector<int>> const& tiempos, int n) {
    int max_tiempos_acum = 0;
    for (int i = n; i > y.k; --i) {
        int maximo = 0;
        for (int j = 1; j <= n; ++j) {
            if (!y.asignado[j]) {
                maximo = max(maximo, tiempos[i][j]);
            }
        }
        max_tiempos_acum += maximo;
    }
    return y.tiempo + max_tiempos_acum;
}

void resolver(vector<vector<int>> const& tiempos, vector<int>& solMejor, int &tiempoMin, int n) {
    priority_queue<tNodo> pq;  //Cola de prioridad de mínimos
    tNodo y;
    y.k = 0;
    vector<bool> marcas(n + 1, false);
    vector<int> sol(n + 1, 0);
    y.tiempo = 0;  //Generamos la raíz del árbol
    y.asignado = marcas;
    y.sol = sol;
    y.tiempo_opt = coste_optimista(y, tiempos, n);

    pq.push(y);

    tiempoMin = coste_pesimista(y, tiempos, n);

    while (!pq.empty() && pq.top().tiempo_opt <= tiempoMin) {
        y = pq.top(); pq.pop();
        //Generamos los hijos de y
        tNodo x; 
        x.sol = y.sol;
        x.k = y.k + 1;
        x.asignado = y.asignado;
        for (int i = 1; i <= n; ++i) {
            if (!x.asignado[i]) {  //Si un hijo no es factible, es descartado
                x.sol[x.k] = i;
                x.asignado[i] = true;
                x.tiempo = y.tiempo + tiempos[x.k][i];
                x.tiempo_opt = coste_optimista(x, tiempos, n);  //Actualizo el coste óptimo estimado
                if (x.tiempo_opt <= tiempoMin) {
                    if (x.k == n) {  //Es solución
                        solMejor = x.sol; tiempoMin = x.tiempo;
                    }
                    else {
                        pq.push(x); 
                        tiempoMin = min(tiempoMin, coste_pesimista(x, tiempos, n));
                    }
                }
                x.asignado[i] = false;
            }
        }
    }
}


bool resuelveCaso() {
    int n; cin >> n;

    if (n == 0)
        return false;

    vector<vector<int>> matriz(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; ++i) {
        matriz[0][i] = 0;
        matriz[i][0] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> matriz[i][j];
        }
    }

    vector<int> solMejor(n + 1, 0);
    int tiempoMin = INT_MAX;
    resolver(matriz, solMejor, tiempoMin, n);
    
    cout << tiempoMin << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
