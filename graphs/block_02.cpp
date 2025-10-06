const int INF = 1e9;
vector<pair<int, int>> adj[N]; // (to, weight)

vector<int> bellman_ford(int n, int src) {
  vector<int> dist(n, INF);
  dist[src] = 0;
  for (int i = 1; i < n; i++) {
    for (int u = 0; u < n; u++) {
      for (auto [v, w] : adj[u]) {
        if (dist[u] < INF && dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
        }
      }
    }
  }
  for (int u = 0; u < n; u++) {
    for (auto [v, w] : adj[u]) {
      if (dist[u] < INF && dist[u] + w < dist[v]) {
        cout << "Negative weight cycle detected!\n";
        return {};
      }
    }
  }
  return dist;
}
