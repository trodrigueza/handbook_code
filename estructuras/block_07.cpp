#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
int st[4*MAXN];     // almacena AND en [tl..tr]
int marked[4*MAXN]; // almacena OR pendiente

// Empuja la máscara OR pendiente a los hijos
void push(int v) {
  if (marked[v] == 0) return;
  st[2*v]     |= marked[v];
  st[2*v+1]   |= marked[v];
  marked[2*v]   |= marked[v];
  marked[2*v+1] |= marked[v];
  marked[v] = 0;
}

// OR bit a bit = new_val para todos i en [l..r]
void update(int v, int tl, int tr, int l, int r, int new_val) {
  if (l > r) return;
  if (l == tl && r == tr) {
    st[v]     |= new_val;
    marked[v] |= new_val; // etiqueta pendiente
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    update(v*2,     tl,    tm,   l, min(r,tm),    new_val);
    update(v*2+1, tm+1,   tr, max(l,tm+1),  r,  new_val);
    st[v] = st[v*2] & st[v*2+1]; // recalcular AND
  }
}

// Consulta AND bit a bit en [l..r]
int query(int v, int tl, int tr, int l, int r) {
  if (l > r) return -1; // -1 = todos bits 1 -> neutro de AND
  if (l == tl && r == tr) {
    return st[v];
  }
  push(v);
  int tm = (tl + tr) / 2;
  int left  = query(v*2,    tl,   tm,   l, min(r,tm));
  int right = query(v*2+1, tm+1,  tr, max(l,tm+1),  r);
  return left & right;
}

// Recorre el árbol e imprime las hojas (valores finales)
void print_leaves(int v, int tl, int tr) {
  if (tl == tr) {
    cout << st[v] << " ";
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    print_leaves(v*2,     tl,   tm);
    print_leaves(v*2+1, tm+1,   tr);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<array<int,3>> queries(m);
  for (int i = 0; i < m; i++) {
    int l, r, q;
    cin >> l >> r >> q;
    queries[i] = {l-1, r-1, q}; // 0-based
  }

  // Inicializar árbol a 0
  for (int i = 0; i < 4*MAXN; i++) {
    st[i] = marked[i] = 0;
  }

  // 1) Aplicar todas las actualizaciones OR por rango
  for (auto &qr : queries) {
    update(1, 0, n-1, qr[0], qr[1], qr[2]);
  }

  // 2) Verificar cada restricción con AND por rango
  for (auto &qr : queries) {
    int res = query(1, 0, n-1, qr[0], qr[1]);
    if (res != qr[2]) {
      cout << "NO\n";
      return 0;
    }
  }

  // 3) Si todo OK, imprimir ``YES'' y el arreglo resultante
  cout << "YES\n";
  print_leaves(1, 0, n-1);
  cout << "\n";
  return 0;
}
