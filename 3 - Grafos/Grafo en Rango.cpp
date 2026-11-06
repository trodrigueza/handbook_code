#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;
vector<pair<int,ll>> g[8 * MAXN];   // nodos: hojas + internos de ambos árboles
int down_[4 * MAXN], up_[4 * MAXN];
int cnt, n;

void add_edge(int a, int b, ll w) { g[a].push_back({b, w}); }

void build(int x, int l, int r) {
    if (l == r) {                    // la hoja es compartida por ambos árboles
        down_[x] = up_[x] = l;
        return;
    }
    down_[x] = cnt++;
    up_[x] = cnt++;
    int m = (l + r) / 2;
    build(2 * x, l, m);
    build(2 * x + 1, m + 1, r);
    add_edge(down_[x], down_[2 * x], 0);
    add_edge(down_[x], down_[2 * x + 1], 0);
    add_edge(up_[2 * x], up_[x], 0);
    add_edge(up_[2 * x + 1], up_[x], 0);
}

// tipo 0: v -> [ql, qr]   |   tipo 1: [ql, qr] -> v
void add_range(int x, int l, int r, int ql, int qr, int v, ll w, int tipo) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        if (tipo == 0) add_edge(v, down_[x], w);
        else           add_edge(up_[x], v, w);
        return;
    }
    int m = (l + r) / 2;
    add_range(2 * x, l, m, ql, qr, v, w, tipo);
    add_range(2 * x + 1, m + 1, r, ql, qr, v, w, tipo);
}

int main() {
    int q, s;
    scanf("%d %d %d", &n, &q, &s);
    cnt = n;                          // los ids 0..n-1 son las hojas
    build(1, 0, n - 1);

    while (q--) {
        int t, v, l, r; ll w;
        scanf("%d %d %d %d %lld", &t, &v, &l, &r, &w);
        if (t == 0) add_range(1, 0, n - 1, l, r, v, w, 0);   // v -> [l,r]
        else        add_range(1, 0, n - 1, l, r, v, w, 1);   // [l,r] -> v
    }

    vector<ll> dist(cnt, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u])
            if (dist[v] > d + w) dist[v] = d + w, pq.push({dist[v], v});
    }
    for (int i = 0; i < n; i++)
        printf("%lld ", dist[i] == LLONG_MAX ? -1 : dist[i]);
}
