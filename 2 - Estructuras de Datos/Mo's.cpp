// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct query {
  int l, r, idx;
  query (int l, int r, int idx) : l(l), r(r), idx(idx) {}
};
int S;
bool cmp (const query &a, const query &b) {
    int A = a.l/S, B = b.l/S;
    if (A != B) return A < B;
    return A & 1 ? a.r > b.r : a.r < b.r;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<query> q;
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        query qq(l-1, r-1, i);
        q.push_back(qq);
    }

    S = sqrt(n);

    unordered_map<int, int> cnt;

    sort(q.begin(), q.end(), cmp);
    int l = 0, r = -1;

    int res = 0;
    auto add = [&](int x) {
        if (cnt[a[x]] == a[x]) res--;
        cnt[a[x]]++;
        if (cnt[a[x]] == a[x]) res++;
    };

    auto del = [&](int x) {
        if (cnt[a[x]] == a[x]) res--;
        cnt[a[x]]--;
        if (cnt[a[x]] == a[x]) res++;
    };

    auto get_ans = [&]() {
        return res;
    };

    vector<int> ans(m);

    for (int i = 0; i < q.size(); ++i) {
        while (r < q[i].r) add(++r);
        while (l > q[i].l) add(--l);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        ans[q[i].idx] = get_ans();
    }

    for (int i : ans) cout << i << "\n";
}
