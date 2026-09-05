// Código handbook --------------------------------------------------------------------
const int MAXN = 10005; // Máximo número de estados (suma de longitudes de patrones)
const int K = 26;      // Tamaño del alfabeto (a-z)
int trie[MAXN][K];     // Transiciones: trie[estado][caracter]
int fail[MAXN];        // Enlaces de fallo
int end_count[MAXN];   // Indica si un estado es el fin de uno o más patrones
int nodes_cnt = 1;     // Contador de nodos (el 0 es la raíz)
// Inserta un patrón en el Trie
void insert(const string& s) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (!trie[u][v]) trie[u][v] = nodes_cnt++;
            u = trie[u][v];
        }
        end_count[u]++; // Marcamos el final de un patrón
}
void build() {
    queue<int> q;
    for (int i = 0; i < K; i++) {
        if (trie[0][i]) q.push(trie[0][i]);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < K; i++) {
                if (trie[u][i]) {
                    fail[trie[u][i]] = trie[fail[u]][i];
                    // Propagamos el conteo de patrones encontrados en sufijos
                    end_count[trie[u][i]] += end_count[fail[trie[u][i]]];
                    q.push(trie[u][i]);
                } else {
                    // Optimización de DFA: el camino inexistente apunta al fallo
                    trie[u][i] = trie[fail[u]][i];
                }
            }
        }
}
int query(const string& text) {
    int u = 0, total_matches = 0;
    for (char c : text) {
        u = trie[u][c - 'a']; // Gracias a la optimización en build(), esto es O(1)
        total_matches += end_count[u];
    }
    return total_matches;
}
