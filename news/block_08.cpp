const long long INF = std::numeric_limits<long long>::max();

// Grafo representado por una lista de adyacencia
// adj[u] = {{v1, w1}, {v2, w2}, ...}
using Edge = std::pair<int, int>; // {vecino, peso}
using Graph = std::vector<std::vector<Edge>>;

// Calcula el peso del MST usando el algoritmo de Prim.
// Retorna -1 si el grafo no es conexo.
long long prim_mst(int n, const Graph& adj) {
    if (n == 0) return 0;
    
    long long total_weight = 0;
    int nodes_in_mst = 0;

    // min_cost[i] guarda el costo mínimo para conectar el nodo i al MST
    std::vector<long long> min_cost(n + 1, INF);
    std::vector<bool> visited(n + 1, false);

    // La cola de prioridad almacena {costo, nodo}.
    // Se usa std::greater para que sea una min-priority queue.
    using State = std::pair<long long, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    // Empezamos desde el nodo 1 (puede ser cualquier nodo)
    int start_node = 1;
    min_cost[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty() && nodes_in_mst < n) {
        long long w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Si el nodo ya fue visitado, lo ignoramos.
        // Esto es clave porque un mismo nodo puede ser insertado múltiples
        // veces en la PQ con diferentes costos.
        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        total_weight += w;
        nodes_in_mst++;

        // Explorar los vecinos del nodo u
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int edge_weight = edge.second;

            // Si v no está en el MST y encontramos una arista más barata para conectarlo
            if (!visited[v] && edge_weight < min_cost[v]) {
                min_cost[v] = edge_weight;
                pq.push({min_cost[v], v});
            }
        }
    }

    // Si no se pudieron visitar todos los nodos, el grafo no es conexo
    if (nodes_in_mst != n) {
        return -1;
    }

    return total_weight;
}

/*
int main() {
    fast_io();
    int n, m;
    std::cin >> n >> m; // n = nodos, m = aristas

    Graph adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // El grafo es no dirigido para MST
    }

    long long mst_weight = prim_mst(n, adj);

    if (mst_weight != -1) {
        std::cout << "El peso total del MST es: " << mst_weight << std::endl;
    } else {
        std::cout << "IMPOSSIBLE" << std::endl; // CSES standard response
    }

    return 0;
}
*/
