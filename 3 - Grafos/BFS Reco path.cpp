#include <bits/stdc++.h>
using namespace std;

struct State {
    int prev, cur;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    set<array<int,3>> forb;
    for (int i = 0; i < k; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--; c--;
        forb.insert({a, b, c});
    }

    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<State>> parent(n, vector<State>(n, {-1, -1}));

    queue<State> q;

    dist[0][0] = 0;
    q.push({0, 0});

    State end_state = {-1, -1};
    bool found = false;

    while (!q.empty()) {
        State s = q.front(); q.pop();
        int prev = s.prev;
        int cur  = s.cur;
        int d    = dist[prev][cur];

        if (cur == n - 1) {
            end_state = s;
            found = true;
            break;
        }

        for (int nxt : g[cur]) {
            if (forb.count({prev, cur, nxt})) continue;

            if (dist[cur][nxt] != INF) continue;

            dist[cur][nxt] = d + 1;
            parent[cur][nxt] = {prev, cur};
            q.push({cur, nxt});
        }
    }

    if (!found) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> path;
    int prev = end_state.prev;
    int cur  = end_state.cur;
    while (true) {
        path.push_back(cur);
        if (prev == 0 && cur == 0) break;
        State p = parent[prev][cur];
        int pp = p.prev;
        int pc = p.cur;
        cur = pc;
        prev = pp;
    }

    reverse(path.begin(), path.end());

    cout << (int)path.size() - 1 << "\n";
    for (int x : path) cout << x + 1 << " ";
    cout << "\n";
}
