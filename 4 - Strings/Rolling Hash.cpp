Rolling Hash. Permite calcular el hash de cualquier subcadena en O(1) despues de un precalculo en O(N).
1. Crear una instancia: RH rh(mi_string);
2. Obtener hash de subcadena s[l..r]: rh.hash_sub(l, r);
Es util para comparar subcadenas rapidamente. Para evitar colisiones, se puede usar doble hashing (dos bases y dos modulos diferentes).

typedef long long ll;
const ll MOD = 1e9+7;
const ll BASE = 31; // 911382323, 137

struct RH {
  vector<ll> pref, power;
  RH(const string& s) {
    int n = (int)s.size();
    pref.resize(n + 1); power.resize(n + 1);
    power[0] = 1;
    for (int i = 0; i < n; i++) {
      pref[i + 1] = (pref[i] * BASE + s[i]) % MOD;
      power[i + 1] = (power[i] * BASE) % MOD;
    }
  }
  ll hash_sub(int l, int r) const {
    ll raw = (pref[r + 1] - (pref[l] * power[r - l + 1]) % MOD + MOD) % MOD;
    return raw;
  }
};

void solve() {
  string s; cin >> s;
  int n = (int)s.size();
  RH rh(s);
  vector<int> a;
  for (int i = 0; i+1 < n; i++) {
    ll h1 = rh.hash_sub(0, i);
    ll h2 = rh.hash_sub(n-i-1, n-1);
    if (h1 == h2){
      a.push_back(i+1);
    }
  }

  auto f = [&](int x) {
    ll h1 = rh.hash_sub(0, x-1);
    for (int i = 1; i + x - 1 < n-1; i++) {
      ll h2 = rh.hash_sub(i, i+x-1);
      if (h1 == h2) {
        return 1;
      }
    }
    return 0;
  };

  int l = 0;
  int r = (int)a.size();
  l--;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (f(a[m])) l = m;
    else r = m;
  }
  if (l < 0 || l >= n) {
    cout << "Just a legend\n";
    return;
  }
  for (int i = 0; i < a[l]; i++)
    cout << s[i];
  cout << "\n";
}
