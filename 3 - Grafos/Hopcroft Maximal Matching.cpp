Código para encontrar maximal matchings, lo que hace es sencillo, varias pasadas de BFS para encontrar
emparejamientos y luego tratará de buscar caminos de aumento con DFS. 
Entonces supongamos que ya se hizo la pasada de BFS, al final quedaron algunos vértices sin emparejar (en el peor de los casos) 
asi que lo que sigue es hacer una dfs desde cada uno de esos nodos que vaya a algún nodo que ya se encuentre emparejado y que siga 
su recorrido hasta encontrar algun nodo no emparejado, lo que esto indicara es que se puede emparejar distinto a como esta emparejado
y entonces permitira emparejar el nodo sin emparejar a un nodo valido., 

int n, k;
vector<vector<int>> g;
vector<int> pairU, pairV, dist;

bool bfs() {
  queue<int> q;
  // Una multibfs desde los nodos no emparejados
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
      // Si no se ha emparejado en el conjunto V entonces se marca como verdadero
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
  // Se manda una bfs mientras se encuentra algo por emparejar, si no se puede pues paila.
  while (bfs()) {
    // Una vez se mandó la bfs entonces se revisa cada nodo en U, si no está emparejado entonces
    // toca buscar un camino de aumento.
    for (int u = 0; u < n; u++) {
      if (pairU[u] == -1 && dfs(u))
	matching++;
    }
  }
  return matching;
}
