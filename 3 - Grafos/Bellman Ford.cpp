Calcula la ruta mas corta desde un nodo fuente a todos los demas en un grafo dirigido con pesos. A diferencia de Dijkstra, funciona con aristas de peso negativo. Su complejidad es O(V * E).
La idea es relajar todas las aristas V-1 veces. Una V-esima iteracion se usa para detectar ciclos de peso negativo: si una distancia aun puede ser mejorada, significa que hay un ciclo negativo.
Diferencia entre ejemplos:
- Ejemplo 1: Implementacion estandar para encontrar el camino mas corto. Inicializa distancias en INF.
- Ejemplo 2: Variacion para encontrar el camino mas largo. Inicializa distancias en -INF y busca maximizar la distancia. Detecta ciclos de peso positivo que son relevantes para la solucion (alcanzables desde el origen y que pueden llegar al destino).

* Ejemplo 1
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


* Ejemplo 2
int32_t main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({v, -w});
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    for (int i = 0; i < n; i++) {
        for (auto &[v, w] : g[i]) {
            w += p[v];
        }
    }

    const int oo = 4e18;
    vector<int> dis(n, -oo);
    dis[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (auto &[v, w] : g[u]) {
                if (dis[u] != -oo && dis[u] + w > dis[v])
                    dis[v] = dis[u] + w;
            }
        }
    }

    vector<int> vis(n, 0);
    auto dfs = [&](int x) {
        stack<int> st;
        vis[x] = 1;
        st.push(x);
        while (st.size()) {
            int cur = st.top(); st.pop();
            for (auto &[y, w] : g[cur]) {
                if (vis[y]) continue;
                vis[y] = 1;
                if (y == t) return true;
                st.push(y);
            }
        }
        return false;
    };

    for (int u = 0; u < n; u++) {
        for (auto &[v, w] : g[u]) {
            if (dis[u] != -oo && dis[u] + w > dis[v] && dis[t] != -oo) {
                if (!vis[u]) dfs(u);
                if (vis[t]) {
                    cout << "Money hack!\n";
                    return 0;
                }
            }
        }
    }
    if (dis[t] == -oo) cout << "Bad trip\n";
    else cout << dis[t];
}
