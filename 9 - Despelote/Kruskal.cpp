// 1. Estructura para representar una arista
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 2. Estructura Disjoint Set Union (DSU) con Path Compression y Union by Size
struct DSU {
    std::vector<int> parent;
    std::vector<int> sz;
    DSU(int n) {
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0); // Rellena 0, 1, 2, ...
        sz.assign(n + 1, 1);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path Compression
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j]) // Union by Size
                std::swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};

// 3. Algoritmo de Kruskal
long long kruskal(int n, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long total_weight = 0;
    int edges_in_mst = 0;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            total_weight += edge.weight;
            edges_in_mst++;
            if (edges_in_mst == n - 1) break; // Optimización
        }
    }

    // Si no se pudieron unir n-1 aristas, el grafo no es conexo
    if (edges_in_mst != n - 1) {
        return -1; // O manejar como un caso especial
    }

    return total_weight;
}

// int main() {
//     fast_io();
//     int n, m;
//     std::cin >> n >> m; // n = nodos, m = aristas
//
//     std::vector<Edge> edges(m);
//     for (int i = 0; i < m; ++i) {
//         std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
//     }
//
//     long long mst_weight = kruskal(n, edges);
//
//     if (mst_weight != -1) {
//         std::cout << "El peso total del MST es: " << mst_weight << std::endl;
//     } else {
//         std::cout << "No es posible formar un MST (el grafo no es conexo)." << std::endl;
//     }
//
//     return 0;
// }
