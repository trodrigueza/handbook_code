// Código handbook ---------------------------------------------------------
const int MAXN = 100005; 
const int K = 26; // Para letras 'a'-'z'
int trie[ MAXN ][ K ];   // Matriz de adyacencia: trie[nodo][caracter]
bool is_end[ MAXN ];   // Marca si un nodo es el final de una palabra
int nodes_cnt = 1;   // Contador de nodos (0 es la raíz)
void insert( const string& s ) {
    int u = 0;
    for (char c : s) {
        int v = c - 'a';
        if (!trie[ u ][ v ]) trie[u][v] = nodes_cnt++;
        u = trie[ u ][ v ];
    }
    is_end[ u ] = true;
}
bool search( const string& s ) {
    int u = 0;
    for ( char c : s ) {
        int v = c - 'a';
        if (!trie[ u ][ v ]) return false;
        u = trie[ u ][ v ];
    }
    return is_end[ u ];
}
bool startsWith( const string& prefix ) {
    int u = 0;
    for ( char c : prefix ) {
        int v = c - 'a';
        if ( !trie[ u ][ v ] ) return false;
        u = trie[ u ][ v ];
    }
    return true;
}
// --------------------------------------------------------------------------
