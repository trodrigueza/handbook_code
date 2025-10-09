* Kosaraju’s Algorithm: Encontrar las componentes fuertemente conexas (SCC) en un grafo dirigido, es decir, grupos de nodos donde cada uno puede alcanzar a los demás.

void dfs1(int v) {
    vis[v] = 1;
    for (auto u : g[v]) if (!vis[u]) dfs1(u);
    order.push_back(v);
}

void dfs2(int v, int id) {
    vis[v] = 1;
    compId[v] = id;
    for (auto u : gt[v]) if (!vis[u]) dfs2(u, id);
}

// Uso:
for (int i = 0; i < n; i++)
    if (!vis[i])
        dfs1(i);
reverse(order.begin(), order.end());
memset(vis, 0, sizeof vis);
int sccCount = 0;
for (auto v : order)
    if (!vis[v])
        dfs2(v, sccCount++);

* Construcción del Grafo Condensado (DAG de SCCs): Convertir las SCCs en un solo nodo cada una, creando un grafo acíclico dirigido (DAG) entre las SCCs.

vector<vector<int>> dag(sccCount);
vector<int> indeg(sccCount, 0);

for (int v = 0; v < n; v++) {
    for (auto u : g[v]) {
        if (compId[v] != compId[u]) {
            dag[compId[v]].push_back(compId[u]);
            indeg[compId[u]]++;
        }
    }
}

* DFS en DAG para Alcanzabilidad

vector<bool> reachable(sccCount, false);
function<void(int)> dfsDag = [&](int v) {
    reachable[v] = true;
    for (auto u : dag[v])
        if (!reachable[u])
            dfsDag(u);
};
dfsDag(compId[s]);

* Conteo de SCC Fuentes No Alcanzables

int ans = 0;
for (int i = 0; i < sccCount; i++) {
    if (!reachable[i] && indeg[i] == 0)
        ans++;
}
