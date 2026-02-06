#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>
#include <list>
#include <string>
#include <queue>

using namespace std;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
//template <typename T = int, typename Comparator = std::less<T>>
template <typename T = int, typename Comparator = std::greater<T>>
//template <typename T = tNodo, typename Comparator = operator<>
class PriorityQueue {

    // vector que contiene los datos
    std::vector<T> array;     // primer elemento en la posición 1

    /* Objeto función que sabe comparar elementos.
     antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
    Comparator antes;

public:

    PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}

    /* Constructor a partir de un vector de elementos */
    PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
        array(v_ini.size() + 1), antes(c) {
        for (auto i = 0; i < v_ini.size(); ++i)
            array[i + 1] = v_ini[i];
        monticulizar();
    }


    /* Insertar el elemento x (que incluye su prioridad).
     Si no hay espacio, el array se agranda. */
    void push(T const& x) {
        array.push_back(x);
        flotar(array.size() - 1);
    }

    /* Devuelve el número de elementos en la cola. */
    int size() const { return int(array.size()) - 1; }

    /* Averigua si la cola con prioridad está vacía. */
    bool empty() const { return size() == 0; }

    /* Si la cola no es vacía, devuelve el elemento más prioritario. */
    T const& top()  const {
        if (empty()) throw std::domain_error("La cola vacia no tiene top");
        else return array[1];
    }

    /* Si la cola no es vacía, elimina el elemento más prioritario. */
    void pop() {
        if (empty())
            throw std::domain_error("Imposible eliminar el primero de una cola vacia");
        else {
            array[1] = std::move(array.back());
            array.pop_back();
            if (!empty()) hundir(1);
        }
    }

    /* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
    void pop(T& prim) {
        if (empty())
            throw std::domain_error("Imposible eliminar el primero de una cola vacia");
        else {
            prim = std::move(array[1]);
            array[1] = std::move(array.back());
            array.pop_back();
            if (!empty()) hundir(1);
        }
    }

private:

    /* Flota el elemento situado en la posición i del montículo. */
    void flotar(int i) {
        T elem = std::move(array[i]);
        int hueco = i;
        while (hueco != 1 && antes(elem, array[hueco / 2])) {
            array[hueco] = std::move(array[hueco / 2]);
            hueco /= 2;
        }
        array[hueco] = std::move(elem);
    }

    /* Hunde el elemento situado en la posición n del montículo. */
    void hundir(int i) {
        T elem = std::move(array[i]);
        int hueco = i;
        int hijo = 2 * hueco; // hijo izquierdo, si existe
        while (hijo <= size()) {
            // cambiar al hijo derecho si existe y va antes que el izquierdo
            if (hijo < size() && antes(array[hijo + 1], array[hijo]))
                ++hijo;
            // flotar el hijo si va antes que el elemento hundiéndose
            if (antes(array[hijo], elem)) {
                array[hueco] = std::move(array[hijo]);
                hueco = hijo; hijo = 2 * hueco;
            }
            else break;
        }
        array[hueco] = std::move(elem);
    }

    /* Convierte un vector en un montículo. */
    void monticulizar() {
        for (auto i = size() / 2; i > 0; --i)
            hundir(i);
    }
};

struct tNodo {
    vector<int> sol;
    vector<bool> limpiados;
    int k;
    int calidad;
    int calidad_opt;
};

bool operator>(tNodo first, tNodo second) {
    return first.calidad_opt > second.calidad_opt;
}

int est_optimista(tNodo& X, const vector<int>& carros, const vector<int>& caminos, const vector<vector<int>>& calidades) {
    int est = X.calidad;
    for (int i = X.k + 1; i < carros.size(); i++) {
        int aux = 0;
        for (int j = 0; j < caminos.size(); j++)
            if (!X.limpiados[j] && caminos[j] >= carros[i])
                aux = max(aux, calidades[i][j]);
        est += aux;
    }
    return est;
}

int quitanieves_rp(const vector<int>& carros, const vector<int>& caminos, const vector<vector<int>>& calidades) {
    tNodo Y;
    Y.limpiados = vector<bool>(caminos.size(), false);
    Y.sol = vector<int>(carros.size(), -1);
    Y.k = -1;
    Y.calidad = 0;
    Y.calidad_opt = est_optimista(Y, carros, caminos, calidades);
    int calidad_max = -1;
    PriorityQueue<tNodo> pq;
    //priority_queue<tNodo> pq;
    pq.push(Y);
    while (!pq.empty() && pq.top().calidad_opt > calidad_max) {
        Y = pq.top();
        pq.pop();
        tNodo X; X.k = Y.k + 1; X.sol = Y.sol; X.limpiados = Y.limpiados;
        for (int i = 0; i < caminos.size(); i++) {
            if (!X.limpiados[i] && carros[X.k] <= caminos[i]) {
                X.limpiados[i] = true;
                X.sol[X.k] = i;
                X.calidad = Y.calidad + calidades[X.k][i];
                X.calidad_opt = est_optimista(X, carros, caminos, calidades);
                if (X.calidad_opt > calidad_max) {
                    if (X.k == carros.size() - 1) {
                        calidad_max = X.calidad;
                    }
                    else pq.push(X);
                }
                X.limpiados[i] = false;
            }
        }
        //No asignamos camino
        X.sol[X.k] = -1;
        X.calidad = Y.calidad;
        X.calidad_opt = est_optimista(X, carros, caminos, calidades);
        if (X.calidad_opt > calidad_max) {
            if (X.k == carros.size() - 1) {
                calidad_max = X.calidad;
            }
            else pq.push(X);
        }
    }
    return calidad_max;
}

void resuelveCaso() {
    int n, m;
    cin >> n >> m;
    vector<int> carros(n);
    vector<int> carros_max(n, 0);
    vector<int> caminos(m);
    for (int i = 0; i < n; i++)
        cin >> carros[i];
    for (int i = 0; i < m; i++)
        cin >> caminos[i];
    vector<vector<int>> calidades(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> calidades[i][j];
            if (calidades[i][j] > carros_max[i])
                carros_max[i] = calidades[i][j];
        }
    }

    int sol = quitanieves_rp(carros, caminos, calidades);

    cout << sol << '\n';
}

int main() {
    int numCasos;
    cin >> numCasos;
    while (numCasos--)
        resuelveCaso();

    return 0;
}