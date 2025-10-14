// Algoritmo de Johnson para contar ciclos en grafo dirigido
// Complejidad O((n+e)(c+1)) dónde c es el número de ciclos.
// No hay uno mejorar así que si piden hallar ciclos seguramente sea este el que hay que usar.
// Verificar que los n+e sean pequeños y si dan información de los ciclos que hay

int count_cycles = 0;

// El stack, y todos los vectores pueden pasarse por referencia o hacerlos globales para quitarle overhead a la llamada de funciones.
void circuit(int v, int s, vector<vector<int>>& A, vector<bool>& blocked, vector<vector<int>>& B, vector<int>& stack) 
{
  stack.push_back(v);
  blocked[v] = true;

  for (int w : A[v]) {
    if (w == s) {
      count_cycles++;
    } else if (!blocked[w]) {
      circuit(w, s, A, blocked, B, stack);
    }
  }

  // desbloquear
  blocked[v] = false;
  stack.pop_back();
}

// Usa el vector como una lista de adyacencias.
int johnson(vector<vector<int>>& G) 
{
  int n = G.size();
  count_cycles = 0;
  vector<bool> blocked(n, false);
  vector<vector<int>> B(n);
  vector<int> stack;

  for (int s = 0; s < n; s++) {
    circuit(s, s, G, blocked, B, stack);
  }
  return count_cycles;
}

