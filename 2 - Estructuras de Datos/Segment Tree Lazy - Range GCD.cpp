* Dos arboles de segmentos para resolver queries de GCD y minimo en un rango [l, r] sobre un arreglo estatico.
build_gcd/build_min: Construye el arbol en O(n).
query_gcd/query_min: Responde una query en O(log n).
Adicionalmente, un mapa 'val_pos' precalcula las posiciones de cada valor para busquedas rapidas.
El problema especifico resuelto es: para un rango [l, r], si el GCD es igual al minimo,
cuenta cuantos elementos no son iguales a ese valor. Si no, la respuesta es la longitud del rango.

const int INF = 1e9;
const ll LLINF = 4e18;
const int MAXN = 1e5 + 5;

int n, t;
int s[MAXN];

int gcd_st[4 * MAXN];
void build_gcd(int v, int tl, int tr) {
  if (tl == tr) {
    gcd_st[v] = s[tl];
  } else {
    int tm = (tl + tr) / 2;
    build_gcd(v * 2, tl, tm);
    build_gcd(v * 2 + 1, tm + 1, tr);
    gcd_st[v] = __gcd(gcd_st[v * 2], gcd_st[v * 2 + 1]);
  }
}

int query_gcd(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (l <= tl && tr <= r) return gcd_st[v];
  int tm = (tl + tr) / 2;
  return __gcd(
    query_gcd(v * 2, tl, tm, l, min(r, tm)),
    query_gcd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
  );
}

int min_st[4 * MAXN];
void build_min(int v, int tl, int tr) {
  if (tl == tr) {
    min_st[v] = s[tl];
  } else {
    int tm = (tl + tr) / 2;
    build_min(v * 2, tl, tm);
    build_min(v * 2 + 1, tm + 1, tr);
    min_st[v] = min(min_st[v * 2], min_st[v * 2 + 1]);
  }
}

int query_min(int v, int tl, int tr, int l, int r) {
  if (l > r) return INF;
  if (l <= tl && tr <= r) return min_st[v];
  int tm = (tl + tr) / 2;
  return min(
    query_min(v * 2, tl, tm, l, min(r, tm)),
    query_min(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
  );
}

map<int, vector<int>> val_pos;

void solve() {
  int l, r; cin >> l >> r;
  l--; r--;

  int g = query_gcd(1, 0, n - 1, l, r);
  int mn = query_min(1, 0, n - 1, l, r);

  if (g != mn) {
    cout << r - l + 1 << '\n';
    return;
  }

  const vector<int>& pos = val_pos[g];
  int cnt = upper_bound(pos.begin(), pos.end(), r) - lower_bound(pos.begin(), pos.end(), l);
  cout << (r - l + 1 - cnt) << "\n";
}

int32_t main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    val_pos[s[i]].push_back(i);
  }

  build_gcd(1, 0, n - 1);
  build_min(1, 0, n - 1);

  cin >> t;
  while (t--) {
    solve();
  }
}
