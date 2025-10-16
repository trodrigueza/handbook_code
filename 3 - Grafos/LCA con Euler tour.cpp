El euler tour nos da una lista de los nodos ordenada por sub arboles, para esto se guarda tanto el tiempo de
entrada de un nodo y además su tiempo de salida, sin embargo este Euler tour tiene una modificación pues para
poder el calcular el lca entre 2 nodos de diferente rama necesito tener su padre dentro del rango en el que aparecen
ambos, porque si no lo tuviera entonces no tendría manera de decir que son de ramas distintas y entonces su
LCA sería el que hubiera entrado antes al euler tour, por eso la modificación.
La modificación es que en el dfs se haga euler_tour[timer++] = node
Para un árbol del tipo 1 -> 2, 1 -> 3 el euler tour normal se vería de la siguiente forma
{1 2 2 3 3 1} en cambio con la modificación es {1 2 1 3 1}, así se calcula el LCA y da 1
NOTA: Es importante mencionar que con el Euler tour + LCA se pueden responder preguntas en caminos entre nodos siempre y cuándo
la operación o la consulta sea invertible. Se calcula la operación desde la raíz hasta cada nodo, luego se calcula el LCA y entre 2 nodos
es la operación hasta a y hasta b - 2 LCA(a,b), si la operación no es invertible, paila.
IMPORTANTE: Revisar los tamaños de los arreglos, esa mierda me dañó.
IMPORTANTE: El ultimo elemento del euler tour esta en timer-1, asi que un for va desde 0 <= i < timer

int n;  // Nodos del árbol
vector<int> graph[100000]; // Árbol con lista de adyacencias.
int timer = 0, tin[100000], euler_tour[200000]; // Timer, tiempo de entrada y el Euler tour
int segtree[800000];  // Segment tree

void dfs(int node = 0, int parent = -1) {
  tin[node] = timer;  // El tiempo de entrada del nodo (el primer momento en que se vió el nodo)
  euler_tour[timer++] = node;
  for (int i : graph[node]) {
    if (i != parent) {
      dfs(i, node);
      euler_tour[timer++] = node; // La modificación.
    }
  }
}

// Se calcula cuál de los 2 entró en un menor tiempo, sin la modificación no se podría hacer esto
int mn_tin(int x, int y) {
  if (x == -1) return y;
  if (y == -1) return x;
  return (tin[x] < tin[y] ? x : y);
}

// Build the segment tree: run build() after running dfs
void build(int node = 1, int l = 0, int r = timer - 1) {
  if (l == r) segtree[node] = euler_tour[l];
  else {
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    segtree[node] = mn_tin(segtree[node * 2], segtree[node * 2 + 1]);
  }
}

int query(int a, int b, int node = 1, int l = 0, int r = timer - 1) {
  if (l > b || r < a) return -1;
  if (l >= a && r <= b) return segtree[node];
  int mid = (l + r) / 2;
  return mn_tin(query(a, b, node * 2, l, mid), query(a, b, node * 2 + 1, mid + 1, r));
}

// Cálcula el LCA
int lca(int a, int b) {
  if (tin[a] > tin[b]) swap(a, b);
  return query(tin[a], tin[b]);
}
