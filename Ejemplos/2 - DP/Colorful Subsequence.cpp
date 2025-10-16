#define int long long

const int NEG_INF = -4e18;

struct State {
  int val;    // valor total
  int color;  // último color
};

int n, k;
vector<int> c, v;
vector<vector<int>> dp;

void solve() 
{
  int n, k;
  cin >> n >> k;
  vector<int> c(n + 1), v(n + 1);
  for (int i = 1; i <= n; i++) cin >> c[i] >> v[i];

  // La dp es de solo 2 capas, para la capa actual solo es necesaria la respuesta para el
  // "piso" anterior, luego hay otro vector con las K opciones para remover y 
  // finalmente se tiene la capa que guarda los últimos mejores colores.
  vector<vector<vector<State>>> dp(2, vector<vector<State>>(k + 1, vector<State>(2, {NEG_INF, -1})));

  // Caso base
  dp[0][0][0] = {0, -1};
  dp[0][0][1] = {0, -2};

  // Se itera por cada bola
  for (int i = 1; i <= n; i++) {
    // Color y valor de la vola actual
    int color = c[i], value = v[i];
    // Capa actual y anterior
    auto& cur = dp[i & 1];
    auto& prev = dp[(i - 1) & 1];

    // La capa actual se debe sobreescribir porque puede 
    // tener elementos basura.
    for (int rem = 0; rem <= k; rem++) {
      cur[rem][0] = {NEG_INF, -1};
      cur[rem][1] = {NEG_INF, -2};
    }

    // Que pasa si no eliminamos la bola actual.
    // Vamos por cada una delas opciones del k, que se refiere a las bolas que quedan
    // por eliminar.
    for (int rem = 0; rem <= k; rem++) {
      // Se usa ese piso con bolas por eliminar, el que corresponde a la capa anterior
      for (auto &st : prev[rem]) {
	if (st.val == NEG_INF) continue;
	if (st.color == color) continue;

	// Como esta vaina está ordenada de mayor a menor entonces basta
	// con agregar esta bola aquí
	cur[rem].push_back({st.val + value, color});
	break;
      }
    }

    // Si eliminamos la bola actual entonces toca meter la bola a la capa actual porque será la última bola que queda
    // y esto se hace por rem-1, pues quedan menos bolas disponibles y queremos modificar lo que hay ahí.
    for (int rem = 1; rem <= k; rem++) {
      for (auto &st : prev[rem - 1]) {
	if (st.val == NEG_INF) continue;
	cur[rem].push_back(st);
      }
    }

    for (int rem = 0; rem <= k; rem++) {
      // Por cada nivel de la última capa con x cantidad de bolas restantes lo que haremos
      // es ordernar los valores y luego crear n nuevo vector limpio con solo 2 elementos, 
      // el mejor y el segundo mejor.
      auto &vec = cur[rem];
      sort(vec.begin(), vec.end(), [](auto &a, auto &b) { return a.val > b.val; });

      // Buscar dos mejores con distinto color
      if (vec.empty()) {
	vec = {{NEG_INF, -1}, {NEG_INF, -2}};
	continue;
      }

      State best = vec[0];
      State second = {NEG_INF, -2};
      for (auto &x : vec) {
	if (x.color != best.color) {
	  second = x;
	  break;
	}
      }

      vec = {best, second};
    }
  }

  int ans = dp[n & 1][k][0].val;
  if (ans < 0) ans = -1;
  cout << ans << '\n';
}
