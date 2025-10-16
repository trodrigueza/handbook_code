La parte importante del código es la función ciclo que encuentra un ciclo en una lista que básicamente funciona como un módulo.
También se puede con BFS y DFS.

pair<int, vector<int>> ciclo(const vector<long long>& v) {
  int N = v.size();
  vector<int> order, seen(N, -1);
  int s = 0;

  while (true) {
    if (seen[s] != -1) {
      int start = seen[s];
      vector<int> cycle;
      for (int i = start; i < (int)order.size(); i++)
	cycle.push_back(order[i]);
      return {start, cycle};
    }
    seen[s] = order.size();
    order.push_back(s);
    s = (s + v[s]) % N;
  }
}

void solve() 
{
  int n, k; cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  auto [start, cycle] = ciclo(v);
  int N = v.size();

  // Lo de antes del ciclo
  vector<int> order;
  int s = 0;
  for (int i = 0; i < start; i++) {
    order.push_back(s);
    s = (s + v[s]) % N;
  }

  int pre_sum = 0;
  // La suma de antes del ciclo
  for (int r : order) pre_sum += v[r];
  // La suma del ciclo
  int cycle_sum = 0;
  for (int r : cycle) cycle_sum += v[r];

  if (k <= (int)start) {
    int ans = 0;
    for (int i = 0, s = 0; i < k; i++) {
      ans += v[s];
      s = (s + v[s]) % N;
    }
    cout << ans << '\n';
    return;
  }

  // K - start es lo que queda luego de tomar la suma de antes del ciclo.
  int rem = k - start;
  int completos = rem / cycle.size();
  int queda = rem % cycle.size();

  int ans = pre_sum + (completos * cycle_sum);

  for (int i = 0; i < queda; i++) ans += v[cycle[i]];

  cout << ans << '\n';
}
