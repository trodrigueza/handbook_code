struct FloydWarshall {
    int n;
    const long long INF = (1LL<<60);
    vector<vector<long long>> dist; // dist[i][j]
    vector<vector<int>> nxt;        // nxt[i][j] para reconstruir camino

    FloydWarshall(int n): n(n), dist(n, vector<long long>(n, INF)),
                          nxt(n, vector<int>(n, -1)) {
        for (int i = 0; i < n; ++i) dist[i][i] = 0, nxt[i][i] = i;
    }

    void add_edge(int u, int v, long long w) {
        if (w < dist[u][v]) dist[u][v] = w, nxt[u][v] = v;
    }

    void run() {
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i) if (dist[i][k] < INF)
                for (int j = 0; j < n; ++j) if (dist[k][j] < INF) {
                    long long nd = dist[i][k] + dist[k][j];
                    if (nd < dist[i][j]) {
                        dist[i][j] = nd;
                        nxt[i][j]  = nxt[i][k]; // saltar hacia el siguiente en i->k
                    }
                }
    }

    bool has_neg_cycle() const {
        for (int i = 0; i < n; ++i) if (dist[i][i] < 0) return true;
        return false;
    }

    // Camino i->j (vacío si no hay camino)
    vector<int> get_path(int i, int j) const {
        if (nxt[i][j] == -1) return {};
        vector<int> path = {i};
        while (i != j) {
            i = nxt[i][j];
            path.push_back(i);
            if ((int)path.size() > n + 5) return {}; // guardia por si acaso
        }
        return path;
    }

    // (Opcional) marcar pares afectados por ciclos negativos con -INF
    void mark_neg_cycles() {
        for (int k = 0; k < n; ++k) if (dist[k][k] < 0)
            for (int i = 0; i < n; ++i) if (dist[i][k] < INF)
                for (int j = 0; j < n; ++j) if (dist[k][j] < INF)
                    dist[i][j] = -INF();
    }

    long long INFval() const { return INF; }
    static long long NEG_INF() { return -(1LL<<62); }
    long long -INF() const { return NEG_INF(); } // alias
};

int main() {
    const long long INF = (1LL<<60);
    int n = 4;
    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    vector<vector<int>> nxt(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) dist[i][i] = 0, nxt[i][i] = i;

    auto add_edge = [&](int u, int v, long long w){
        if (w < dist[u][v]) dist[u][v] = w, nxt[u][v] = v;
    };

    // Aristas dirigidas
    add_edge(0,1,4);
    add_edge(0,2,11);
    add_edge(0,3,10);
    add_edge(1,2,-2);  // negativa permitida
    add_edge(1,3,8);
    add_edge(2,3,3);

    // Floyd–Warshall
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) if (dist[i][k] < INF)
            for (int j = 0; j < n; ++j) if (dist[k][j] < INF) {
                long long nd = dist[i][k] + dist[k][j];
                if (nd < dist[i][j]) dist[i][j] = nd, nxt[i][j] = nxt[i][k];
            }

    // Imprime matriz de distancias
    cout << "Distancias APSP:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << (dist[i][j] >= INF/2 ? "INF" : to_string(dist[i][j])) << " ";
        cout << "\n";
    }

    // Reconstruye camino 0 -> 3
    int s = 0, t = 3;
    if (nxt[s][t] == -1) { cout << "No hay camino\n"; return 0; }
    vector<int> path = {s};
    while (s != t) { s = nxt[s][t]; path.push_back(s); }

    cout << "Camino 0->3: ";
    for (int v : path) cout << v << " ";
    cout << "\nCosto: " << dist[path.front()][path.back()] << "\n";
}
