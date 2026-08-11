// ~ O( 1 )
struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) { a = find(a), b = find(b); if (a == b) return false; p[a] = b; return true; }
};

// rollback, O( log n ) sin path compression
struct DSU {
    vector<int> p, sz;
    vector<pair<int&,int>> history;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        history.push_back({p[b], p[b]});
        history.push_back({sz[a], sz[a]});
        p[b] = a; sz[a] += sz[b];
        return true;
    }
    int snapshot() { return history.size(); }
    void rollback(int t) {
        while ((int)history.size() > t) {
            history.back().first = history.back().second;
            history.pop_back();
        }
    }
};
