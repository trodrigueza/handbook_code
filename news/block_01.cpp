const int MAXN = 200005;

// Estructura de datos subyacente: Segment Tree
long long tree[4 * MAXN], values[MAXN];
void build_st(int node, int start, int end) {
    if (start == end) {
        tree[node] = values[start];
        return;
    }
    int mid = (start + end) / 2;
    build_st(2 * node, start, mid);
    build_st(2 * node + 1, mid + 1, end);
    tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
}

void update_st(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update_st(2 * node, start, mid, idx, val);
    } else {
        update_st(2 * node + 1, mid + 1, end, idx, val);
    }
    tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
}

long long query_st(int node, int start, int end, int l, int r) {
    if (r < start || end < l || l > r) {
        return 0; // Identidad para la operación max
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    long long p1 = query_st(2 * node, start, mid, l, r);
    long long p2 = query_st(2 * node + 1, mid + 1, end, l, r);
    return std::max(p1, p2);
}

// Implementación de HLD
std::vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], subtree_size[MAXN];
int chain_head[MAXN], base_pos[MAXN];
int current_pos;

// 1. DFS para calcular tamaños de subárbol, profundidad y padre
void dfs_size(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_size(v, u, d + 1);
        subtree_size[u] += subtree_size[v];
    }
}

// 2. DFS para la descomposición
void dfs_hld(int u, int p, int head) {
    chain_head[u] = head;
    base_pos[u] = current_pos++;

    int heavy_child = -1, max_size = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (subtree_size[v] > max_size) {
            max_size = subtree_size[v];
            heavy_child = v;
        }
    }

    if (heavy_child != -1) {
        dfs_hld(heavy_child, u, head);
    }

    for (int v : adj[u]) {
        if (v == p || v == heavy_child) continue;
        dfs_hld(v, u, v); // Inicia una nueva cadena
    }
}

// Consulta de HLD en la ruta u-v
long long query_path(int u, int v, int n) {
    long long res = 0;
    while (chain_head[u] != chain_head[v]) {
        if (depth[chain_head[u]] < depth[chain_head[v]]) std::swap(u, v);
        res = std::max(res, query_st(1, 0, n - 1, base_pos[chain_head[u]], base_pos[u]));
        u = parent[chain_head[u]];
    }
    if (depth[u] > depth[v]) std::swap(u, v);
    res = std::max(res, query_st(1, 0, n - 1, base_pos[u], base_pos[v]));
    return res;
}

void init_hld(int n, int root) {
    current_pos = 0;
    dfs_size(root, -1, 0);
    dfs_hld(root, -1, root);
}

// int main() {
//     fast_io();
//     int n, q;
//     std::cin >> n >> q;
//     long long node_values[n];
//     for (int i = 0; i < n; ++i) std::cin >> node_values[i];
//
//     for (int i = 0; i < n - 1; ++i) {
//         int u, v;
//         std::cin >> u >> v;
//         --u; --v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }
//
//     init_hld(n, 0);
//
//     // Mapear valores de nodos a la estructura base
//     for(int i = 0; i < n; ++i) {
//         values[base_pos[i]] = node_values[i];
//     }
//     build_st(1, 0, n - 1);
//
//     while (q--) {
//         int type;
//         std::cin >> type;
//         if (type == 1) {
//             int s;
//             long long x;
//             std::cin >> s >> x;
//             --s;
//             update_st(1, 0, n - 1, base_pos[s], x);
//         } else {
//             int u, v;
//             std::cin >> u >> v;
//             --u; --v;
//             std::cout << query_path(u, v, n) << " ";
//         }
//     }
//     std::cout << std::endl;
//
//     return 0;
// }
