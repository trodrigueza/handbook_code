Dado un grafo aciclico dirigido (DAG), ordena los nodos linealmente de tal manera que si existe una arista entre los nodos u y v entonces u aparece antes que v.
Este ordenamiento es una manera de poner todos los nodos en una linea recta de tal manera que las aristas vayan de izquierda a derecha.

const int MX = 1e5+5;
vector<int> g[MX];
vector<int> state; 
deque<int> order; 
int n, m;
bool has_cycle;

void toposort(int u) {
    state[u] = 1;
    for (auto &v : g[u]) {
        if (state[v] == 1) has_cycle = true;     
        else if (state[v] == 0) toposort(v);
    }
    state[u] = 2;
    order.push_front(u);

}

void init() {
    order.clear();
    state.assign(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        g[i].clear();
    }
    has_cycle = 0;
}

Variante iterativa: Devuelve true si existe orden topologico (queda en `order`),
false si hay ciclo

bool toposort() {
    vector<int> state(n + 1, 0), it(n + 1, 0); // 0 blanco, 1 gris, 2 negro
    vector<int> order;
    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        stack<int> st;
        st.push(s); state[s] = 1;
        while (!st.empty()) {
            int u = st.top();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (state[v] == 1) return false;          // nodo gris => ciclo
                if (state[v] == 0) { state[v] = 1; st.push(v); }
            } else {
                state[u] = 2;          // ya proceso todos sus vecinos
                order.push_back(u);
                st.pop();
            }
        }
    }
    reverse(order.begin(), order.end());
    return true;
}

Algoritmo de Kahn: Devuelve true si existe orden topologico (queda en `order`), false si hay ciclo
Se adapta directo a variantes que aparecen seguido: cambiar la queue por priority_queue
da el orden topológico lexicográficamente mínimo, y procesar por niveles te sirve para DP sobre DAGs
(camino más largo, contar caminos, etc.).

bool toposort() {
    vector<int> indeg(n + 1, 0);
    vector<int> order;
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) indeg[v]++;
    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return (int)order.size() == n;
}
