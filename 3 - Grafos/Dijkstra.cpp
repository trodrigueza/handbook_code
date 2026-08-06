Dijkstra O(m log n), pesos no negativos. Distancias en ll.
g[u] = {v, w}. INF = 4e18.

vector<ll> dijkstra(int s, vector<vector<pair<int,ll>>>& g) {
    int n = g.size();
    vector<ll> d(n, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != d[u]) continue;          // entrada vieja, saltar
        for (auto [v, w] : g[u])
            if (du + w < d[v]) {
                d[v] = du + w;
                pq.push({d[v], v});
            }
    }
    return d;
}
