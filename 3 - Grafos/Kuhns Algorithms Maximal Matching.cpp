*Algoritmo de Hopcroft-Karp para maximum bipartite matching.
Complejidad: O(E * sqrt(V)).

Uso:
- n: Nodos en la particion izquierda (0 a n-1).
- k: Nodos en la particion derecha (0 a k-1).
- g: Lista de adyacencia de tamano n. g[u] son los vecinos de u en la particion derecha.
- Llamar a hopcroft_karp() devuelve el tamano del matching.
- El matching se guarda en pairU y pairV.

int n, k;
vector<vector<int>> g;
vector<int> pairU, pairV, dist;

bool bfs() {
  queue<int> q;
  for (int u = 0; u < n; u++) {
    if (pairU[u] == -1) {
      dist[u] = 0;
      q.push(u);
    } else {
      dist[u] = -1;
    }
  }

  bool found = false;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u]) {
      int pu = pairV[v];
      if (pu == -1) found = true;
      else if (dist[pu] == -1) {
	dist[pu] = dist[u] + 1;
	q.push(pu);
      }
    }
  }
  return found;
}

bool dfs(int u) {
  for (int v : g[u]) {
    int pu = pairV[v];
    if (pairV[v] == -1 || (dist[pu] == dist[u] + 1 && dfs(pu))) {
      pairU[u] = v;
      pairV[v] = u;
      return true;
    }
  }
  dist[u] = -1;
  return false;
}

int hopcroft_karp() {
  pairU.assign(n, -1);
  pairV.assign(k, -1);
  dist.assign(n, -1);

  int matching = 0;
  while (bfs()) {
    for (int u = 0; u < n; u++) {
      if (pairU[u] == -1 && dfs(u))
	matching++;
    }
  }
  return matching;
}
