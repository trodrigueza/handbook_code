String Hashing (Doble Hash). Permite comparar substrings en O(1).
Precalculo en O(N): `DoubleHash dh(s);`
Obtener hash de s[l..r]: `dh.get(l, r);` // o(1)
Comparar s[l1..r1] y s[l2..r2]: `dh.equal(l1, r1, l2, r2);` // o(1)
Usa dos modulos para mayor robustez.

struct DoubleHash {
  const ll mod[2]  = {(ll)1e9+7, (ll)1e9+9};
  const ll base[2] = {911382323LL, 972663749LL};

  vector<array<ll,2>> pref, pw;

  DoubleHash(const string& s) {
    int n = (int)s.size();
    pref.assign(n + 1, {0,0});
    pw.assign(n + 1, {1,1});
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < 2; k++) {
        pref[i + 1][k] = (pref[i][k] * base[k] + s[i]) % mod[k];
        pw[i + 1][k]   = (pw[i][k]   * base[k]) % mod[k];
      }
    }
  }

  pll get(int l, int r) const {
    array<ll,2> h{};
    for (int k = 0; k < 2; k++) {
      ll cur = (pref[r + 1][k] - pref[l][k] * pw[r - l + 1][k]) % mod[k];
      if (cur < 0) cur += mod[k];
      h[k] = cur;
    }
    return {h[0], h[1]};
  }

  bool equal(int l1, int r1, int l2, int r2) const {
    return get(l1, r1) == get(l2, r2);
  }
};

void solve() {
  string s; cin >> s;
  int n = (int)s.size();
  DoubleHash rh(s);
  vector<int> a;
  for (int i = 0; i+1 < n; i++) {
    if (rh.equal(0, i, n-i-1, n-1)){
      a.push_back(i+1);
    }
  }

  auto f = [&](int x) {
    for (int i = 1; i + x - 1 < n-1; i++) {
      if (rh.equal(0, x-1, i, i+x-1)) {
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
