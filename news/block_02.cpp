const long long INF = std::numeric_limits<long long>::max();

// Grafo representado por una lista de adyacencia
// adj[u] = {{v1, w1}, {v2, w2}, ...}
using Edge = std::pair<int, int>; // {vecino, peso}
using Graph = std::vector<std::vector<Edge>>;

void dijkstra(int start_node, int n, const Graph& adj, std::vector<long long>& dist) {
    dist.assign(n + 1, INF);
    dist[start_node] = 0;

    // La cola de prioridad almacena {distancia, nodo}
    // Se usa std::greater para que sea una min-priority queue
    using State = std::pair<long long, int>; // {distancia, nodo}
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push({0, start_node});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Optimización: si ya encontramos un camino más corto, ignoramos este estado
        if (d > dist[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// int main() {
//     fast_io();
//     int n, m;
//     std::cin >> n >> m; // n = nodos, m = aristas
//
//     Graph adj(n + 1);
//     for (int i = 0; i < m; ++i) {
//         int u, v, w;
//         std::cin >> u >> v >> w;
//         adj[u].push_back({v, w});
//         // Para grafos no dirigidos, anadir: adj[v].push_back({u, w});
//     }
//
//     std::vector<long long> distances;
//     dijkstra(1, n, adj, distances);
//
//     for (int i = 1; i <= n; ++i) {
//         std::cout << "Distancia desde 1 a " << i << " es: " << (distances[i] == INF ? "INF" : std::to_string(distances[i])) << "\n";
//     }
//
//     return 0;
// }
