const int K = 26;

struct Node {
    int next[K];
    bool st = false; // ¿Es el final de una palabra?
    int sf = 0;      // Enlace de sufijo (suffix link)
    int output = -1; // Enlace de salida (output link)
    vector<int> ids; // IDs de las palabras que terminan aquí

    Node() {
        fill(begin(next), end(next), -1);
    }
};

vector<Node> aho(1);

void insert(const string& str, int idx) {
    int actual = 0;
    for (char ch : str) {
        int c = ch - 'a';
        if (aho[actual].next[c] == -1) {
            aho[actual].next[c] = aho.size();
            aho.emplace_back();
        }
        actual = aho[actual].next[c];
    }
    aho[actual].st = true;
    aho[actual].ids.push_back(idx);
}

// ✨ Función optimizada para crear todos los enlaces
void make_links_optimized() {
    queue<int> q;

    // Inicializar los hijos directos de la raíz
    for (int i = 0; i < K; ++i) {
        if (aho[0].next[i] != -1) {
            q.push(aho[0].next[i]);
        } else {
            // Los fallos desde la raíz apuntan a la raíz misma
            aho[0].next[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < K; ++i) {
            int v = aho[u].next[i];
            if (v == -1) {
                // Si no hay transición directa, usamos el enlace de sufijo del nodo actual
                // para encontrar la siguiente transición.
                aho[u].next[i] = aho[aho[u].sf].next[i];
                continue;
            }

            // v es un hijo directo, calculamos su enlace de sufijo
            aho[v].sf = aho[aho[u].sf].next[i];
            
            // Calculamos su enlace de salida
            aho[v].output = aho[aho[v].sf].st ? aho[v].sf : aho[aho[v].sf].output;
            
            q.push(v);
        }
    }
}

// ✨ Función de búsqueda mucho más simple y rápida
vector<int> search(const string& text, int sz) {
    vector<int> matches(sz, 0);
    int actual = 0;

    for (char ch : text) {
        int c = ch - 'a';
        
        // Ya no se necesita el bucle while. La transición es directa.
        actual = aho[actual].next[c];

        // Recolectar coincidencias directas en este nodo
        if (aho[actual].st) {
            for (auto id : aho[actual].ids) {
                matches[id]++;
            }
        }

        // Recolectar coincidencias a través de los enlaces de salida
        int out = aho[actual].output;
        while (out != -1) {
            for (auto id : aho[out].ids) {
                matches[id]++;
            }
            out = aho[out].output;
        }
    }

    return matches;
}

int main() {
    // Ejemplo de uso
    vector<string> patterns = {"he", "she", "his", "hers"};
    string text = "ushers";

    for (int i = 0; i < patterns.size(); ++i) {
        insert(patterns[i], i);
    }

    make_links_optimized();

    vector<int> result = search(text, patterns.size());

    cout << "Coincidencias encontradas:" << endl;
    for (int i = 0; i < patterns.size(); ++i) {
        if (result[i] > 0) {
            cout << "- '" << patterns[i] << "': " << result[i] << " vez/veces" << endl;
        }
    }

    return 0;
}
