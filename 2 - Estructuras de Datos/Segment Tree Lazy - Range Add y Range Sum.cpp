* Segment Tree con Lazy Propagation.
- updateRange(1, 0, n-1, l, r, val): Suma val a cada elemento en el rango [l, r].
- queryRange(1, 0, n-1, l, r): Devuelve la suma del rango [l, r].
- El arbol se construye sobre un arreglo de ceros.

const int MAXN = 100000;
ll st[4*MAXN], lazy[4*MAXN];

// Propaga la etiqueta pendiente desde v a sus hijos
void push(int v, int tl, int tr) {
  if (lazy[v] == 0) return;
  int tm = (tl + tr) / 2;
  // hijo izquierdo recibe add = lazy[v]
  lazy[v*2] += lazy[v];
  st[v*2] += lazy[v] * (tm - tl + 1);
  // hijo derecho recibe add = lazy[v]
  lazy[v*2+1] += lazy[v];
  st[v*2+1]   += lazy[v] * (tr - (tm+1) + 1);
  lazy[v] = 0;
}

// Actualiza: a[i] += add_val para todo i en [l..r]
void updateRange(int v, int tl, int tr, int l, int r, ll add_val) {
  if (l > r) return;
  if (l == tl && r == tr) {
    st[v] += add_val * (tr - tl + 1);
    lazy[v] += add_val;
  } else {
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    updateRange( v*2, tl, tm, l, min(r,tm), add_val);
    updateRange(v*2+1, tm+1, tr, max(l,tm+1), r, add_val);
    st[v] = st[v*2] + st[v*2+1];
  }
}

// Consulta la suma en [l..r], nodo v cubre [tl..tr]
ll queryRange(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (l == tl && r == tr) return st[v];
  push(v, tl, tr);
  int tm = (tl + tr) / 2;
  return queryRange(v*2, tl, tm, l, min(r,tm))
       + queryRange(v*2+1, tm+1,tr, max(l,tm+1), r);
}

int32_t main() {
  int n, q; cin >> n >> q;
  // Inicializar a 0
  for (int i = 0; i < 4*MAXN; i++)
    st[i] = lazy[i] = 0;

  while (q--) {
    int type; cin >> type;
    if (type == 1) {
      int l, r; ll add_val; cin >> l >> r >> add_val;
      updateRange(1, 0, n-1, l, r, add_val);
    } else {
      int l, r; cin >> l >> r;
      cout << queryRange(1, 0, n-1, l, r) << "\n";
    }
  }
}
