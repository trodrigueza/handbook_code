Funciona para arboles y para grafo, si se quiere mas compacto para arboles entonces quitar el
vector de visitados.

int n;  // Nodos del árbol
vector<int> graph[200005]; // Árbol con lista de adyacencias.
int timer = 0, tin[200005], euler_tour[400005]; // Timer, tiempo de entrada y el Euler tour
vector<bool> vis(200005, false);

void dfs(int node = 1, int parent = -1) {
  vis[node] = true;
  tin[node] = timer;
  euler_tour[timer++] = node;
  for (int i : graph[node]) {
    if (!vis[i]) {
      dfs(i, node);
      euler_tour[timer++] = node;
    }
  }
}

