const int MAXN = 1000005;
const int INF = 2e9; // Represents negative infinity for max operations
vector<int> adj[MAXN];
int n;

// --- Preprocessing Data ---
int g_dist[MAXN];
int dist_a[MAXN], dist_b[MAXN], eccentricity[MAXN];

// --- Centroid Decomposition Data ---
int subtree_size[MAXN];
bool removed[MAXN];
bool ans[MAXN];

// Utility BFS to find distances from a start node
pair<int, int> bfs(int start_node) {
    fill(g_dist + 1, g_dist + n + 1, -1);
    vector<int> q;
    q.reserve(n);
    q.push_back(start_node);
    g_dist[start_node] = 0;
    
    int head = 0;
    int farthest_node = start_node;

    while(head < q.size()){
        int u = q[head++];
        if(g_dist[u] > g_dist[farthest_node]){
            farthest_node = u;
        }
        for(int v : adj[u]){
            if(g_dist[v] == -1){
                g_dist[v] = g_dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    return {farthest_node, g_dist[farthest_node]};
}

// --- Centroid Decomposition Functions ---

void get_subtree_sizes(int u, int p, vector<int>& component_nodes) {
    subtree_size[u] = 1;
    component_nodes.push_back(u);
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            get_subtree_sizes(v, u, component_nodes);
            subtree_size[u] += subtree_size[v];
        }
    }
}

int find_centroid(int u, int p, int total_size) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && subtree_size[v] * 2 > total_size) {
            return find_centroid(v, u, total_size);
        }
    }
    return u;
}

void get_branch_data(int u, int p, int d, vector<pair<int, int>>& branch_nodes) {
    branch_nodes.push_back({u, d});
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            get_branch_data(v, u, d + 1, branch_nodes);
        }
    }
}

void decompose(int start_node) {
    vector<int> component_nodes;
    component_nodes.reserve(n);
    get_subtree_sizes(start_node, -1, component_nodes);
    int c = find_centroid(start_node, -1, subtree_size[start_node]);

    vector<vector<pair<int, int>>> branches;
    vector<int> m_values;

    for (int v : adj[c]) {
        if (!removed[v]) {
            vector<pair<int, int>> current_branch_data;
            get_branch_data(v, c, 1, current_branch_data);
            branches.push_back(current_branch_data);
            
            int max_m = -INF;
            for(auto const& [node, dist_from_c] : current_branch_data){
                max_m = max(max_m, dist_from_c - eccentricity[node]);
            }
            m_values.push_back(max_m);
        }
    }

    int m_max1 = -INF, m_max2 = -INF;
    for(int m : m_values){
        if(m >= m_max1){
            m_max2 = m_max1;
            m_max1 = m;
        } else if (m > m_max2){
            m_max2 = m;
        }
    }
    
    if (m_max1 >= 0) ans[c] = true;

    for (size_t i = 0; i < branches.size(); ++i) {
        int m_other = (m_values[i] == m_max1) ? m_max2 : m_max1;
        if(m_other == -INF) continue; 

        for (auto const& [u, dist_from_c] : branches[i]) {
            if (dist_from_c + m_other >= 0) {
                ans[u] = true;
            }
        }
    }
    
    removed[c] = true;
    for (int v : adj[c]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Phase 1: Precomputation
    pair<int, int> fa = bfs(1);
    int a = fa.first;
    pair<int, int> fb = bfs(a);
    int b = fb.first;
    
    copy(g_dist + 1, g_dist + n + 1, dist_a + 1);
    bfs(b);
    copy(g_dist + 1, g_dist + n + 1, dist_b + 1);

    for(int i = 1; i <= n; ++i){
        eccentricity[i] = max(dist_a[i], dist_b[i]);
    }
    
    // Phase 2: Centroid Decomposition
    decompose(1);

    string result_str = "";
    for (int i = 1; i <= n; ++i) {
        result_str += (ans[i] ? '1' : '0');
    }
    cout << result_str << "\n";

    return 0;
}
