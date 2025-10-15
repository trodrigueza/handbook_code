OPTIMIZACION
ESTA MIERDA ES RE IMPORTANTE.

vector<int> weigth, value;

vector<int> dp;
int n;

void solve() 
{
  int w; cin >> n >> w;
  weigth.resize(n); value.resize(n);
  for (int i = 0; i < n; i++) cin >> weigth[i] >> value[i];
  int total = accumulate(value.begin(), value.end(), 0LL);
  dp.resize(total+5);
  fill(dp.begin(), dp.end(), oo);

  // Entonces veamos como si nuestra maleta no estuviera limitada por el peso sino por el value, 
  // veamos todos los valores que podemos tener y entonces respondemos la pregunta de si para cada peso
  // que necesitan esos valores entonces se pueden obtener.

  dp[0] = 0;
  // Aquí miramos si cogemos el valor o ñao
  for (int i = 0; i < n; i++) {
    for (int j = total; j >= 0; j--) {
      // Es decir, para ese precio tenemos opción de comprarlo o no, si compramos pues le restamos.
      if (j - value[i] >= 0) {
	dp[j] = min(dp[j], dp[j - value[i]] + weigth[i]);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i <= total; i++) 
    if (dp[i] <= w) ans = i;
  cout << ans << '\n';
}
