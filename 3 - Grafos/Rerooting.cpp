Esta tecnica es goat, se basa en la relacion de los elementos del arbol con la raiz, si nos movemos un paso hacia algun lado pues nos alejamos de algun lado pero nos acercamos en otro y es ese el principio que se usa para resolver estos problemas.

int N;
vector<vector<int>> g;
vector<int> sub, dp, ans;

void dfs(int v, int p) 
{
  // Un nuevo elemento.
  sub[v] = 1;
  // Suma de distancias hasta aquí.
  dp[v] = 0;
  for (auto a : g[v]) {
    // Si es el padre se continua
    if (a == p) continue;
    dfs(a, v);
    // Aquí ya está calculada la info para a
    sub[v] += sub[a];
    // Tengo la suma de distancias  hasta a pero 
    // de ellas me alejo la cantidad de nodos abajo mio (sub[a])
    dp[v] += sub[a] + dp[a];
  }
}

void reroot(int v, int p) 
{
  // Se calcula la respuesta: 
  ans[v] = dp[v];
  for (auto a : g[v]) {
    if (a == p) continue;
    int pv = dp[v], pt = dp[a];
    int sv = sub[v], st = sub[a];

    // Le restamos porque nos acercamos más a esos nodos
    dp[v] -= (pt + st);
    // Los nodos de debajo de a ya no se cuentan porque no nos alejamos de ellos
    sub[v] -= (st);
    // Se suma la cantidad de nodos de los que nos alejamos y el valor
    dp[a] += dp[v] + sub[v];
    // Ahora nos alejamos de un montón de nodos entonces lo sumamos.
    sub[a] += sub[v];
    // Porque ya actualizamos
    reroot(a, v);

    // Restauramos valores previos porque ya se asignó la respuesta real.
    dp[v] = pv, dp[a] = pt; 
    sub[v] = sv, sub[a] = st;
  }
}

void solve()
{
  cin >> N;
  g.resize(N+1);
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  sub.assign(N + 1, 0);
  dp.assign(N + 1, 0);
  ans.assign(N + 1, 0);

  dfs(1, 0);
  reroot(1, 0);

  for (int i = 1; i <= N; i++) cout << ans[i] << '\n';
}

int32_t main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  //cin >> t;
  while (t--) solve();
}
