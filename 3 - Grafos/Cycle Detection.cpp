Determina si un grafo dirigido tiene o no ciclos (si es un DAG o no).
La idea es que si es posible llegar a un vértice visitado por medio de otro camino
entonces se encuentra un ciclo.

const int MX = 1e5+5; // Cantidad maxima de nodos
vector<int> g[MX]; // Lista de adyacencia
vector<int> vis; // Marca el estado de los nodos ya visitados
bool cycle; // true si el grafo tiene ciclos
int n, m; // Cantidad de nodos y aristas

void dfs(int u) {
  if (cycle) return;
  vis[u] = 1;
  for (auto &v : g[u]) {
    // Si no se había visito aún.
    if (!vis[v]) dfs(v);
    // Si se visitó una vez y se llegó a él nuevamente entonces hay un ciclo.
    else if (vis[v] == 1) {
      cycle = true;
      break;
    }
  }
  // Esto es para asegurar que ya se revisó la secuencia de 
  // vértices que empieza en u y que por tanto si otra secuencia visita a u
  // entonces que no sea como ciclo.
  vis[u] = 2;
}

void init() {
  // La idea es usar el grafo 0 indexado.
  vis.assign(n, 0);
  for (int i = 0; i < n; i++) 
    g[i].clear();

  // Que solo se lance mientras el nodo no haya sido
  // visitado antes.
  for (int i = 0; i < n; i++) 
    if (!vis[i]) dfs(i);
  
  // if (cycle)  entonces tiene al menos un ciclo.
}
