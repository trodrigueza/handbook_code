Floyd-Warshall APSP O(n^3). Pesos negativos OK.
Uso: dist[i][j]=INF, dist[i][i]=0, nxt[i][i]=i;
     arista: dist[u][v]=min(dist[u][v],w), nxt[u][v]=v;
Tras run(): dist[i][j]=-INF si pasa por ciclo negativo.

const ll INF = 1e18;
vector<vector<ll>> dist; vector<vector<int>> nxt;

void run(int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) if (dist[i][k] < INF)
            for (int j = 0; j < n; j++) if (dist[k][j] < INF)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j], nxt[i][j] = nxt[i][k];
    for (int k = 0; k < n; k++) if (dist[k][k] < 0)      // ciclos negativos
        for (int i = 0; i < n; i++) if (dist[i][k] < INF)
            for (int j = 0; j < n; j++) if (dist[k][j] < INF)
                dist[i][j] = -INF;
}

vector<int> get_path(int i, int j) { // vacio si no hay camino
    if (nxt[i][j] == -1 || dist[i][j] == -INF) return {};
    vector<int> p = {i};
    while (i != j) p.push_back(i = nxt[i][j]);
    return p;
}
