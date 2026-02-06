// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

#include "Grafo.h"

using namespace std;

struct tSol {
    int sol; 
    bool conectada;
};

tSol resolver(Grafo const& G) {
    tSol sol; sol.conectada = true; sol.sol = 0;
    for (int s = 0; s < G.V() && sol.conectada; s++){ 
        vector<bool> visit(G.V(), false);
        vector<int> dist(G.V(), 0);
        queue<int> q;
        int num_visitados = 1;

        q.push(s); visit[s] = true;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : G.ady(v)) {
                if (!visit[w]) {
                    visit[w] = true;
                    dist[w] = dist[v] + 1;
                    q.push(w);

                    sol.sol = max(sol.sol, dist[w]);
                    num_visitados++;
                }
            }
        }

        if (num_visitados != G.V()) sol.conectada = false;
    }
    return sol;
}

bool resuelveCaso() {
    int num_personas, num_relaciones;
    cin >> num_personas >> num_relaciones;

    if (!std::cin)
        return false;

    map<string, int> vertices_nomb;
    map <int, string> vertices_num;

    Grafo G(num_personas);

    string nombre_1, nombre_2;
    int pers_actuales = 0;
    for (int i = 0; i < num_relaciones; ++i){
        cin >> nombre_1 >> nombre_2;
        if (!vertices_nomb.count(nombre_1)) {
            vertices_nomb.insert({ nombre_1, pers_actuales });
            vertices_num.insert({ pers_actuales, nombre_1 });
            pers_actuales++;
        }
        if (!vertices_nomb.count(nombre_2)) {
            vertices_nomb.insert({ nombre_2, pers_actuales });
            vertices_num.insert({ pers_actuales, nombre_2 });
            pers_actuales++;
        }
        int n_1 = vertices_nomb.at(nombre_1);
        int n_2 = vertices_nomb.at(nombre_2);
        G.ponArista(n_1, n_2);
    }

    tSol sol = resolver(G);

    if (sol.conectada == false) cout << "DESCONECTADA\n";
    else cout << sol.sol << '\n';


    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}