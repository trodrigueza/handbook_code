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

Otra versión, esta es la original, metiendo el tiempo de salida solo al final.

int n, m;
vector<int> graph[MAXN];
int a[MAXN];
int tin[MAXN], tout[MAXN], euler_tour[MAXN], depth[MAXN];
int timer = 0;

int seg[4*MAXN], lazy[4*MAXN];

void dfs(int node = 1, int parent = -1, int d = 0) 
{
  depth[node] = d;
  tin[node] = timer;
  euler_tour[timer++] = node;
  for (int v : graph[node]) {
    if (v == parent) continue;
    dfs(v, node, d + 1);
  }
  tout[node] = timer - 1;
}

