Algoritmo de Euclides Extendido.
Encuentra x, y tal que a*x + b*y = gcd(a, b).
La funcion retorna el gcd(a, b). Los valores de x, y se guardan en las variables pasadas por referencia.
Complejidad: O(log(min(a, b))).

int extEuclid(int a, int b, int &x, int &y) {
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
    return a; // gcd(a, b)
}
