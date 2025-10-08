struct Dijkstra {
    int n;
    const long long INF = (1LL<<60);
    vector<vector<pair<int,long long>>> g; // g[u] = {v, w}

    Dijkstra(int n): n(n), g(n) {}

    void add_edge(int u, int v, long long w, bool undirected=false){
        // PRE: w >= 0
        g[u].push_back({v, w});
        if (undirected) g[v].push_back({u, w});
    }

    pair<vector<long long>, vector<int>> run(int s) const {
        vector<long long> dist(n, INF);
        vector<int> parent(n, -1);
        using P = pair<long long,int>;
        priority_queue<P, vector<P>, greater<P>> pq;

        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != dist[u]) continue; // lazy deletion
            for (auto [v, w] : g[u]) {
                // si sospechas de negativos en input:
                // if (w < 0) throw runtime_error("Dijkstra necesita w>=0");
                long long nd = du + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    parent[v] = u;
                    pq.push({nd, v});
                }
            }
        }
        return {dist, parent};
    }

    static vector<int> get_path(int s, int t, const vector<int>& parent){
        if (s==t && parent[t]==-1) return {s};
        if (parent[t]==-1) return {};
        vector<int> path;
        for (int v = t; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    const long long INF = (1LL<<60);
    int n = 6;
    vector<vector<pair<int,long long>>> g(n);

    auto add_undirected = [&](int u, int v, long long w){
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    };

    // Grafo no dirigido (todos w >= 0)
    add_undirected(0,1,7);
    add_undirected(0,2,9);
    add_undirected(0,5,14);
    add_undirected(1,2,10);
    add_undirected(1,3,15);
    add_undirected(2,3,11);
    add_undirected(2,5,2);
    add_undirected(3,4,6);
    add_undirected(4,5,9);

    int s = 0, t = 4;
    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);

    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[s] = 0; pq.push({0, s});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            long long nd = du + w; // w >= 0
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    // Distancias desde 0
    cout << "Distancias desde 0:\n";
    for (int i = 0; i < n; ++i)
        cout << "0->" << i << " = " << dist[i] << "\n";

    // Reconstrucción de 0->4
    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Camino 0->4: ";
    for (int v : path) cout << v << " ";
    cout << "\nCosto: " << dist[t] << "\n";
}
