const int MAXN = 100000 + 5;
int N;
vector<int> g[MAXN];
long long sub[MAXN];
long long answer = 0;

void dfs(int u, int p) {
    sub[u] = 1;  // cuenta el propio u
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        // tamaño del lado del subárbol de v es sub[v]
        long long s = sub[v];
        answer += s * (N - s);
        sub[u] += sub[v];
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);
    cout << answer << "\n";
    return 0;
}
