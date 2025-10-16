Aho-Corasick. Encuentra todas las ocurrencias de un conjunto de patrones (diccionario) en un texto.
Complejidad: O(|texto| + |diccionario|).
1. Anadir cada patron al diccionario con add_string().
2. Para procesar el texto, iterar sobre sus caracteres y transicionar en el automata:
   int estado_actual = 0;
   for (char c : texto) {
     estado_actual = go(estado_actual, c);
     // aqui se procesan los matches. Un match ocurre si t[estado_actual].output es true.
     // Para encontrar todos los matches que terminan en la posicion actual,
     // se debe seguir la cadena de suffix links (get_link) desde el estado_actual
     // hasta la raiz y chequear el flag 'output' en cada nodo.
   }

// m: total length of all considered words.
// k: size of dictionary.
const int K = 26;

struct Vertex {
  int next[K]; // use a map to make this O(m) space (O(mlogk) in time, instead of O(m))
  bool output = false;
  int p = -1;
  char pch;
  int link = -1;
  int go[K];

  Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
    fill(begin(next), end(next), -1);
    fill(begin(go), end(go), -1);
  }
};

vector<Vertex> t(1);

void add_string(string const& s) {
  int v = 0;
  for (char ch : s) {
    int c = ch - 'a';
    if (t[v].next[c] == -1) {
      t[v].next[c] = t.size();
        t.emplace_back(v, ch);
      }
    v = t[v].next[c];
  }
  t[v].output = true;
}

int go(int v, char ch);

int get_link(int v) {
  if (t[v].link == -1) {
    if (v == 0 || t[v].p == 0)
      t[v].link = 0;
    else
      t[v].link = go(get_link(t[v].p), t[v].pch);
  }
  return t[v].link;
}

int go(int v, char ch) {
  int c = ch - 'a';
  if (t[v].go[c] == -1) {
    if (t[v].next[c] != -1)
      t[v].go[c] = t[v].next[c];
    else
      t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
  }
  return t[v].go[c];
}
