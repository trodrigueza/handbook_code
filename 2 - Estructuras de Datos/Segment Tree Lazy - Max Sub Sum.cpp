#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e5+3;
int a[N];

struct Node {
  int total, bp, bs, ans;
};

Node st[4*N];
void build (int v, int tl, int tr) {
  if (tl == tr) {
    st[v].ans = a[tl];
    st[v].bp = a[tl];
    st[v].bs = a[tl];
    st[v].total = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(2*v, tl, tm);
    build(2*v+1, tm+1, tr);
    st[v].total = st[2*v].total + st[2*v+1].total;
    st[v].bp = max(st[2*v].bp, st[2*v].total + st[2*v+1].bp);
    st[v].bs = max(st[2*v+1].bs, st[2*v+1].total + st[2*v].bs);
    st[v].ans = max(st[2*v].ans, st[2*v+1].ans);
    st[v].ans = max(st[v].ans, st[2*v].bs + st[2*v+1].bp);
  }
}

Node query (int v, int tl, int tr, int l, int r) {
  if (l > r) return {0, 0, 0, 0};
  if (l <= tl && r >= tr) return st[v];
  int tm = (tl + tr) / 2;

  if (r <= tm) {
    return query(2*v, tl, tm, l, r);
  }
  if (l > tm) {
    return query(2*v+1, tm+1, tr, l, r);
  }
  auto left = query(2*v, tl, tm, l, min(r, tm));
  auto right = query(2*v+1, tm+1, tr, max(l, tm+1), r);

  if (!left.ans && !left.bs && !left.bp && !left.total) {
    return right;
  }
  if (!right.ans && !right.bs && !right.bp && !right.total) {
    return left;
  }

  Node ans;
  ans.total = left.total + right.total;
  ans.bp = max(left.bp, left.total + right.bp);
  ans.bs = max(right.bs, right.total + left.bs);
  ans.ans = max(left.ans, right.ans);
  ans.ans = max(ans.ans, left.bs + right.bp);
  return ans;
}

void update(int v, int tl, int tr, int pos, int val) {
  if (tl == tr) {
    st[v].ans = val;
    st[v].bp = val;
    st[v].bs = val;
    st[v].total = val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(2*v, tl, tm , pos, val);
    } else {
      update(2*v+1, tm+1, tr, pos, val);
    }
    st[v].total = st[2*v].total + st[2*v+1].total;
    st[v].bp = max(st[2*v].bp, st[2*v].total + st[2*v+1].bp);
    st[v].bs = max(st[2*v+1].bs, st[2*v+1].total + st[2*v].bs);
    st[v].ans = max(st[2*v].ans, st[2*v+1].ans);
    st[v].ans = max(st[v].ans, st[2*v].bs + st[2*v+1].bp);
  }
}

void solve() {
  int n; cin >> n;
  for (int i = 0; i <n; i++) {
    cin >> a[i];
  }

  build(1, 0, n-1);

  int m; cin >> m;
  while (m--) {
    int qt, x, y; cin >> qt >> x >> y;
    if (qt) {
      cout << query(1, 0, n-1, x-1, y-1).ans << "\n";
    } else {
      update(1, 0, n-1, x-1, y);
    }
  }
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  while (t--) {
    solve();
  }
}
