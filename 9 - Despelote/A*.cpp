const int INF = std::numeric_limits<int>::max();

struct Node {
    int x, y; // Coordenadas
    int g_cost; // Costo desde el inicio
    int h_cost; // Costo heurístico
    
    int f_cost() const { return g_cost + h_cost; }

    // Para la cola de prioridad (ordenar por f_cost)
    bool operator>(const Node& other) const {
        return f_cost() > other.f_cost();
    }
};

// Función heurística (Distancia de Manhattan)
int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int a_star(const std::vector<std::vector<int>>& grid, Node start, Node goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Movimientos posibles (arriba, abajo, izquierda, derecha)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    std::vector<std::vector<int>> g_costs(rows, std::vector<int>(cols, INF));
    
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    
    start.g_cost = 0;
    start.h_cost = heuristic(start.x, start.y, goal.x, goal.y);
    pq.push(start);
    g_costs[start.x][start.y] = 0;

    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();

        if(current.x == goal.x && current.y == goal.y){
            return current.g_cost; // Objetivo alcanzado
        }
        
        // Optimización: si el costo actual es peor que uno ya encontrado
        if(current.g_cost > g_costs[current.x][current.y]){
            continue;
        }

        for(int i = 0; i < 4; ++i){
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i];

            if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && grid[new_x][new_y] != 1){ // 1 = obstáculo
                int new_g_cost = current.g_cost + 1; // Suponiendo costo de movimiento = 1
                if(new_g_cost < g_costs[new_x][new_y]){
                    g_costs[new_x][new_y] = new_g_cost;
                    Node neighbor = {new_x, new_y, new_g_cost, heuristic(new_x, new_y, goal.x, goal.y)};
                    pq.push(neighbor);
                }
            }
        }
    }
    
    return -1; // No se encontró camino
}

// int main() {
//     fast_io();
//     // Ejemplo: Grid 5x5 con un obstáculo
//     std::vector<std::vector<int>> grid = {
//         {0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0},
//         {0, 0, 0, 0, 0},
//         {0, 1, 1, 1, 0},
//         {0, 0, 0, 0, 0}
//     };
//
//     Node start = {0, 0};
//     Node goal = {4, 4};
//
//     int cost = a_star(grid, start, goal);
//
//     if(cost != -1){
//         std::cout << "El costo del camino más corto es: " << cost << std::endl;
//     } else {
//         std::cout << "No se encontró un camino." << std::endl;
//     }
//
//     return 0;
// }
