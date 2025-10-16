KMP - Encontrar el prefijo mas largo que es tambien sufijo y aparece en medio.
La funcion solve() recibe un string s.
Calcula el border array (funcion de prefijo) de KMP.
Luego, busca el prefijo mas largo de s que tambien es sufijo de s y que ademas aparece como subcadena en el interior de s.
Si existe, imprime esa subcadena. Si no, imprime "Just a legend".
Uso: Llamar a solve() dentro de main. La entrada se lee de cin.

void solve() {
  string s; cin >> s;
  int n = (int)s.size();
  vector<int> Border(n+1);
  Border[0] = -1;
  int j = -1;

  for (int i = 0; i < n; i++) {
    while (j >= 0 && s[i] != s[j])
      j = Border[j];
    j++;
    Border[i+1] = j;
  }
  int tmp = n;
  int ans = -1;
  while (Border[tmp] > 0 && ans == -1) {
    for (int i = 0; i < n; i++) {
      if (Border[i] == Border[tmp]) {
        ans = Border[i];
        break;
      }
    }
    tmp = Border[tmp];
  }
  if (ans == -1) {
    cout << "Just a legend\n";
    return;
  }
  for (int i = 0; i < ans; i++)
    cout << s[i];
  cout << "\n";
}
