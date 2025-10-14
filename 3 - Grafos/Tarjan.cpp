Pa encontrar los puentes en un grafo no dirigido, se necesita tener el tiempo de entrada de cada nodo 
y el tiempo más antiguo (pequeño/lejano) alcanzable desde el vértice actual, entonces por ejemplo
si quito una arista entonces el tiempo de más antiguo de los 2 vértices incidentes, digamos (u, to) se remueve
entonces si low[u] < low[to] significa que esa vaina es un puente porque entonces u puede alcanzar un nodo anterior al 
de to y eso hace que se rompa la componente.

Retorna una lista de los puentes en el grafo y mediante esta uno podría armar un grafo sin puentes.
Que tambien sirve por ejemplo con DSU para saber si hay un camino fijo entre 2 nodos.

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> g[MAXN];
int n, m;
vector<pair<int,int>> bridges;

int timer = 0;
int tin[MAXN], low[MAXN];
bool visited[MAXN];

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;

  for (int to : g[v]) {
    if (to == p) continue; // No mirar la arista por donde llegamos
    if (visited[to]) {
      // Arista de retroceso
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);

      if (low[to] > tin[v]) {
	bridges.push_back({v, to}); // Encontramos un puente
      }
    }
  }
}

void find_bridges() {
  timer = 0;
  fill(visited, visited + n, false);
  for (int i = 0; i < n; i++) {
    if (!visited[i])
      dfs(i);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    --u; --v; // indexación desde 0
    g[u].push_back(v);
    g[v].push_back(u);
  }

  find_bridges();

  cout << "Puentes encontrados:\n";
  for (auto [u, v] : bridges)
    cout << u+1 << " " << v+1 << "\n";
}
