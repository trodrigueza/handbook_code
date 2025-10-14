Util para encontrar la cantidad de ciclos simples en un grafo no dirigido. 
Pero solo sirve si la cantidad de vértices es <= 15


#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> g;
vector<bool> vis;
int count_cycles = 0;

// DFS que busca ciclos simples
void dfs(int start, int v, int parent) {
  vis[v] = true;
  for (int u : g[v]) {
    if (u == start && parent != start) {
      count_cycles++;
    } else if (!vis[u] && u > start) {
      dfs(start, u, v);
    }
  }
  vis[v] = false;
}

// Función principal para contar todos los ciclos simples
int countAllCycles() {
  count_cycles = 0;
  for (int i = 0; i < n; i++) {
    // Se reinicia el arreglo de visitados.
    vis.assign(n, false);
    dfs(i, i, -1);
  }
  return count_cycles / 2; // cada ciclo se cuenta dos veces
}

int main() {
  cin >> n >> m;
  g.assign(n, {});
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    a--, b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  cout << "Cantidad de ciclos simples: " << countAllCycles() << "\n";
}

