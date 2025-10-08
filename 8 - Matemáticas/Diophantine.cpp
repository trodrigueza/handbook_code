Encuentra x, y en la ecuación de la forma ax + by = c
El algoritmo de Euclides extendido retorna el gcd(a, b) y calcula los coeficientes enteros X y Y que satisfacen la ecuacion: a*X + b*Y = gcd(a, b).

int x, y;
// O(log(max(a, b)))
int euclid(int a, int b) {
    if (b == 0) { x = 1; y = 0; return a; }
    int d = euclid(b, a%b);
    int aux = x;
    x = y;
    y = aux - a/b*y;
    return d;
}

ll g;
bool diophantine(ll a, ll b, ll c) {
    x = y = 0;
    if (!a && !b) return (!c); // sólo hay solución con c = 0
    g = euclid(abs(a), abs(b));
    if (c % g) return false;
    a /= g; b /= g; c /= g;
    if (a < 0) x *= -1;
    x = (x % b) * (c % b) % b;
    if (x < 0) x += b;
    y = (c - a*x) / b;
    return true;
}
