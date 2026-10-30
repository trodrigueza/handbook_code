String Hashing (Doble Hash). Permite comparar substrings en O(1).
Precalculo en O(N): `DoubleHash dh(s);`
Obtener hash de s[l..r]: `dh.get(l, r);` // o(1)
Comparar s[l1..r1] y s[l2..r2]: `dh.equal(l1, r1, l2, r2);` // o(1)
Usa dos modulos para mayor robustez.

struct DoubleHash {
  const ll mod[2]  = {(ll)1e9+7, (ll)1e9+9};
  const ll base[2] = {911382323LL, 972663749LL};

  vector<array<ll,2>> pref, pw;
  int n;
  vector<int> str;
  array<ll,2> full;   // hash de [0, n-1]


  DoubleHash(const vector<int>& s) : n((int)s.size()) , str(s) {
    int n = (int)s.size();
    pref.assign(n + 1, {0,0});
    pw.assign(n + 1, {1,1});
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < 2; k++) {
        pref[i + 1][k] = (pref[i][k] * base[k] + s[i]) % mod[k];
        pw[i + 1][k]   = (pw[i][k]   * base[k]) % mod[k];
      }
    }
    full = pref[n];
  }

  array<ll,2> get(int l, int r) const {
    array<ll,2> h{};
    for (int k = 0; k < 2; k++) {
      ll cur = (pref[r + 1][k] - pref[l][k] * pw[r - l + 1][k]) % mod[k];
      if (cur < 0) cur += mod[k];
      h[k] = cur;
    }
    return h;
  }

  array<ll,2> update(int x, int c) {
	  for (int k = 0; k < 2; k++) {
		  ll diff = ((ll)c - str[x]+mod[ k ]) % mod[k];
		  if (diff < 0) diff += mod[k];
		  full[k] = (full[k] + diff * pw[n - 1 - x][k]) % mod[k];
	  }
	  str[ x ]  = c;
	  return full;
  }

  bool equal(int l1, int r1, int l2, int r2) const {
    return get(l1, r1) == get(l2, r2);
  }
};
