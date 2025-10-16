SCC Cuenta el numero de componentes fuertemente conexas en un grafo dirigido dado, ademas este codigo tambien cuenta desde cualquier nodo cual es el numero de componentes que puede y no puede alcanzar, tiene una complejidad de O(V+E)

const int MAXN = 5005;

int n, m;
vector<int> g[MAXN], gt[MAXN]; // grafo original y transpuesto

vector<int> order, compId;
vector<bool> vis;
vector<vector<int>> dag; // grafo condensado (SCCs)
vector<int> indeg;       // grado de entrada por SCC
vector<int> topo;        // orden topológico de las SCCs

// ====== Primera pasada: DFS en grafo original ======
void dfs1(int v) 
{
    vis[v] = true;
    for (int u : g[v]) if (!vis[u]) dfs1(u);
    order.push_back(v);
}

// ====== Segunda pasada: DFS en grafo transpuesto ======
void dfs2(int v, int id) 
{
    vis[v] = true;
    compId[v] = id;
    for (int u : gt[v]) if (!vis[u]) dfs2(u, id);
}

// ====== Kosaraju principal ======
int kosaraju() 
{
    order.clear();
    vis.assign(n, false);
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs1(i);

    reverse(order.begin(), order.end());
    vis.assign(n, false);
    compId.assign(n, -1);
    int sccCount = 0;

    for (int v : order)
        if (!vis[v]) dfs2(v, sccCount++);

    // ====== Construcción del DAG condensado ======
    dag.assign(sccCount, {});
    indeg.assign(sccCount, 0);

    for (int v = 0; v < n; v++) {
        for (int u : g[v]) {
            if (compId[v] != compId[u]) {
                dag[compId[v]].push_back(compId[u]);
                indeg[compId[u]]++;
            }
        }
    }

    // ====== Orden topológico de las SCCs ======
    topo.clear();
    queue<int> q;
    vector<int> indeg_copy = indeg;
    for (int i = 0; i < sccCount; i++)
        if (indeg_copy[i] == 0) q.push(i);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        topo.push_back(v);
        for (int u : dag[v])
            if (--indeg_copy[u] == 0)
                q.push(u);
    }

    return sccCount;
}

vector<bool> markReachableFromSCC(int startSCC) 
{
    int S = (int)dag.size();
    vector<bool> reach(S, 0);
    if (startSCC < 0) return reach;
    function<void(int)> dfs = [&](int v) {
        reach[v] = 1;
        for (int u : dag[v]) if (!reach[u]) dfs(u);
    };
    dfs(startSCC);
    return reach;
}

void solve() 
{
  cin >> n >> m;
  int k; cin >> k; k--;
  for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    from--, to--;
    g[from].push_back(to);
    gt[to].push_back(from);
  }

  int total = kosaraju();
  int sccStart = compId[k];
  auto reachable = markReachableFromSCC(sccStart);
  int ans = 0;
  for (int i = 0; i < total; i++) {
    if (indeg[i] == 0 and !reachable[i]) ans++;
  }
  cout << ans << '\n';
}
