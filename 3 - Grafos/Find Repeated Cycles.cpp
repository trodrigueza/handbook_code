* Aqui se cuentan  el número de caminos cerrados de longitud K.
Usa potencias de la matriz de adyacencia pero tengo entendido que no se puede con matrix exponentiation
funciona para n <= 50 y k <= 10, cuenta la cantidad de ciclos de longitud k
NOTA: No funciona con matrix exponentiation porque para hallar k = 10 se necesita k = 9 y así
sucesivamente, solo funcionaría para contar la cantidad de ciclos de especifica longitud.

using Matrix = vector<vector<long long>>;

// Multiplicación de matrices
Matrix mult(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Contar ciclos de longitud <= kmax
long long countCyclesAdjMatrix(Matrix A, int kmax) {
    int n = A.size();
    Matrix M = A;
    long long total = 0;
    for (int k = 1; k <= kmax; k++) {
        long long trace = 0;
        for (int i = 0; i < n; i++) trace += M[i][i];
        total += trace / k;
        M = mult(M, A);
    }
    return total;
}

int main() {
    int n, m; cin >> n >> m;
    Matrix A(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        A[a][b] = 1;
        A[b][a] = 1; // comentar esta línea si es dirigido
    }

    int kmax = 5; // contar ciclos hasta longitud 5
    cout << "Ciclos (con repeticiones, hasta longitud " << kmax << "): "
         << countCyclesAdjMatrix(A, kmax) << "\n";
}

// --------------------------------------------------------------------------
using Matrix = vector<vector<long long>>;

Matrix mult(const Matrix& A, const Matrix& B, long long mod = 1e9+7) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}

Matrix mat_pow(Matrix A, long long K, long long mod = 1e9+7) {
    int n = A.size();
    Matrix R(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (K > 0) {
        if (K & 1) R = mult(R, A, mod);
        A = mult(A, A, mod);
        K >>= 1;
    }
    return R;
}

int main() {
    int n, m; long long K;
    cin >> n >> m >> K;
    Matrix A(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        A[a][b] = 1;
        A[b][a] = 1; // comentar si es dirigido
    }

    Matrix Ak = mat_pow(A, K);
    long long trace = 0;
    for (int i = 0; i < n; i++) trace = (trace + Ak[i][i]) % 1000000007;
    cout << "Ciclos cerrados de longitud " << K << ": "
         << (trace * ((1000000007 + 1) / K % 1000000007)) % 1000000007 << "\n";
}
