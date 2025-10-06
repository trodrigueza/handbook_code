#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100000;
ll a[MAXN], st[4*MAXN];

// Construye el árbol en st[], cubre [tl..tr]
void build(int v, int tl, int tr) {
  if (tl == tr) {
    st[v] = a[tl]; // valor en la hoja
  } else {
    int tm = (tl + tr) / 2;
    build(v*2,     tl,   tm);    // hijo izquierdo -> [tl..tm]
    build(v*2+1,  tm+1, tr);     // hijo derecho -> [tm+1..tr]
    st[v] = st[v*2] + st[v*2+1]; // suma de los hijos
  }
}

// Consulta la suma en el rango [l..r], nodo v cubre [tl..tr]
ll query(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;               // rango vacío -> 0 neutro
  if (l == tl && r == tr) return st[v];
  int tm = (tl + tr) / 2;
  // sumo recursivamente las partes de izquierda y derecha
  return query(v*2, tl,    tm,   l, min(r,tm))
       + query(v*2+1,tm+1, tr, max(l,tm+1), r);
}

// Actualiza punto pos = new_val, nodo v cubre [tl..tr]
void update(int v, int tl, int tr, int pos, ll new_val) {
  if (tl == tr) {
    st[v] = new_val; // hoja
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(v*2,     tl,   tm,   pos, new_val);
    } else {
      update(v*2+1,  tm+1, tr,   pos, new_val);
    }
    st[v] = st[v*2] + st[v*2+1];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  build(1, 0, n-1);

  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int pos;
      ll val;
      cin >> pos >> val;
      // 0-based
      update(1, 0, n-1, pos, val);
    } else {
      int l, r;
      cin >> l >> r;
      // 0-based
      cout << query(1, 0, n-1, l, r) << "\n";
    }
  }
  return 0;
}
