Sumas de prefijos 2D para contar componentes conexas en una submatriz.
La idea se basa en la caracteristica de Euler para grafos (V - E).
El numero de componentes es el numero de nodos ('1') menos el numero de aristas (pares adyacentes de '1').
Se precalculan tres matrices de sumas de prefijos:
1. Para los nodos ('1's).
2. Para las aristas horizontales (dos '1's adyacentes horizontalmente).
3. Para las aristas verticales (dos '1's adyacentes verticalmente).
Cada consulta se responde en O(1) restando los valores precalculados.
Complejidad: O(N*M) para precalculo, O(1) por consulta.
Uso: Modificar la logica de 'b', 'h', 'v' segun la definicion de nodo y arista del problema.

int32_t main() {
  int n, m, q; cin >> n >> m >> q;
  vector<string> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];


  vector<vector<int>> b(n+1, vector<int>(m+1, 0));
  vector<vector<int>> h(n+1, vector<int>(m+1, 0));
  vector<vector<int>> v(n+1, vector<int>(m+1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int cur = (a[i-1][j-1] == '1' ? 1 : 0);
      int up = i > 1 ? (a[i-2][j-1] == '1' ? 1 : 0) : -1;
      int left = j > 1 ? (a[i-1][j-2] == '1' ? 1 : 0) : -1;

      b[i][j] = cur;
      if (j > 1 && cur && left) h[i][j] = 1;
      if (i > 1 && cur && up) v[i][j] = 1;

      b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
      h[i][j] += h[i-1][j] + h[i][j-1] - h[i-1][j-1];
      v[i][j] += v[i-1][j] + v[i][j-1] - v[i-1][j-1];
    }
  }

  auto f = [&](vector<vector<int>> &ps, int x1, int y1, int x2, int y2) {
    return ps[x2][y2] - ps[x1-1][y2] - ps[x2][y1-1] + ps[x1-1][y1-1];
  };

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int total_blue = f(b, x1, y1, x2, y2);
    int hor = f(h, x1, y1+1, x2, y2);
    int ver = f(v, x1+1, y1, x2, y2);

    cout << total_blue - hor - ver << "\n";
  }
}
