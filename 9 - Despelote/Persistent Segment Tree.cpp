const int MAXN = 100005;

// Nodo del árbol. Se usan punteros para la persistencia.
struct Node {
    Node *left = nullptr, *right = nullptr;
    int count = 0;

    Node(int c) : count(c) {}
    Node(Node* l, Node* r) : left(l), right(r) {
        if (l) count += l->count;
        if (r) count += r->count;
    }
};

// Construye un árbol vacío inicial.
void build(Node* &curr, int tl, int tr) {
    curr = new Node(0);
    if (tl == tr) return;
    int tm = tl + (tr - tl) / 2;
    build(curr->left, tl, tm);
    build(curr->right, tm + 1, tr);
}

// Actualización persistente: crea una nueva versión del árbol.
// Retorna un puntero a la nueva raíz.
Node* update(Node* prev, int tl, int tr, int pos, int val) {
    // Crea un nuevo nodo en la ruta de actualización
    Node* curr = new Node(0);
    if (tl == tr) {
        curr->count = prev->count + val;
        return curr;
    }
    
    int tm = tl + (tr - tl) / 2;
    // Reutiliza los punteros a hijos que no cambian
    curr->left = prev->left;
    curr->right = prev->right;

    if (pos <= tm) {
        curr->left = update(prev->left, tl, tm, pos, val);
    } else {
        curr->right = update(prev->right, tm + 1, tr, pos, val);
    }
    
    curr->count = curr->left->count + curr->right->count;
    return curr;
}

// Consulta el k-ésimo elemento en el rango representado por las versiones `l_root` y `r_root`.
int query(Node* l_root, Node* r_root, int tl, int tr, int k) {
    if (tl == tr) {
        return tl;
    }

    int tm = tl + (tr - tl) / 2;
    int left_count = r_root->left->count - l_root->left->count;

    if (k <= left_count) {
        return query(l_root->left, r_root->left, tl, tm, k);
    } else {
        return query(l_root->right, r_root->right, tm + 1, tr, k - left_count);
    }
}

Node* versions[MAXN]; // Almacena las raíces de todas las versiones

/*
int main() {
    fast_io();
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    std::vector<int> distinct_vals;
    for(int i = 0; i < n; ++i) {
        std::cin >> a[i];
        distinct_vals.push_back(a[i]);
    }
    
    // 1. Coordinar la compresión de valores
    std::sort(distinct_vals.begin(), distinct_vals.end());
    distinct_vals.erase(std::unique(distinct_vals.begin(), distinct_vals.end()), distinct_vals.end());
    
    auto get_compressed_val = [&](int val) {
        return std::lower_bound(distinct_vals.begin(), distinct_vals.end(), val) - distinct_vals.begin();
    };
    
    int max_coord = distinct_vals.size();
    
    // 2. Construir el árbol de segmentos persistente
    build(versions[0], 0, max_coord - 1);
    for (int i = 0; i < n; ++i) {
        int compressed_val = get_compressed_val(a[i]);
        versions[i + 1] = update(versions[i], 0, max_coord - 1, compressed_val, 1);
    }
    
    // 3. Responder consultas
    for (int i = 0; i < q; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k; // Consulta en rango 1-based [l, r]
        int compressed_res = query(versions[l - 1], versions[r], 0, max_coord - 1, k);
        std::cout << distinct_vals[compressed_res] << "\n";
    }

    return 0;
}
*/
