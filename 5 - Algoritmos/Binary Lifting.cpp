Binary Lifting, la idea es como lograr hacer aplicaciones de funciones, como encontrar el k-esimo ancestro de un nodo con una complejidad de O(log n).

vector<int> apps;
vector<int> a;

int apply (int j) {
  return apps[j]-1;
}

void solve() {
  vector<vector<int>> dp(61, vector<int>(2e5));
  int n, k; cin >> n >> k;
  a.resize(n);
  apps.resize(n);

  for (int i = 0; i < n; i++) cin >> apps[i];
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) dp[0][i] = apply(i);

  for (int p = 1; p < 61; p++) {
    for (int i = 0; i < n; i++) {
      dp[p][i] = dp[p-1][ dp[p-1][i] ];
    }
  }

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    int pos = i;
    for (int p = 0; p < 61; p++)
      if ((k >> p) & 1)
	pos = dp[p][pos];
    ans[i] = a[pos];
  }
  for (auto a : ans) cout << a << ' ';
  cout << '\n';
}

Ejemplo 2
int32_t main() {
    int n; cin >> n;
    vector<int> h(n-1);
    for (int i = 0; i < n-1; i++) cin >> h[i];

    vector<int> l(n-1, -1), r(n-1, -1);
    stack<int> st;
    for (int i = 0; i < n-1; i++) {
        if (st.empty()) { st.push(i); continue; }
        while (st.size() && h[i] > h[st.top()]) st.pop();
        if (st.size()) l[i] = st.top();
        st.push(i);
    }

    st = {};
    for (int i = n - 2; i >= 0; i--) {
        if (st.empty()) { st.push(i); continue; }
        while (st.size() && h[i] > h[st.top()]) st.pop();
        if (st.size()) r[i] = st.top();
        st.push(i);
    }


    vector<vector<ll>>step_right(22, vector<ll>(n - 1, 0));
    vector<vector<ll>>step_left(22, vector<ll>(n - 1, 0));
    vector<vector<ll>>sum_right(22, vector<ll>(n - 1, 0));
    vector<vector<ll>>sum_left(22, vector<ll>(n - 1, 0));

    for (int i = 0; i < n-1; i++) {
        if(l[i] == -1){
            step_left[0][i] = i;
            sum_left[0][i] = 0;
        } else {
            sum_left[0][i] = (i - l[i]) * h[i];
            step_left[0][i] = l[i];
        }
        if(r[i] == -1){
            step_right[0][i] = i;
            sum_right[0][i] = 0;
        } else {
            sum_right[0][i] = (r[i] - i) * h[i];
            step_right[0][i] = r[i];
        }
    }

    for(int k = 1; k < 22; k++){
        for(int i = 0 ; i < n - 1; ++ i){
            step_left[k][i] = step_left[k - 1][step_left[k - 1][i]];
            step_right[k][i] = step_right[k - 1][step_right[k - 1][i]];
            sum_left[k][i] = sum_left[k - 1][i] + sum_left[k - 1][step_left[k - 1][i]];
            sum_right[k][i] = sum_right[k - 1][i] + sum_right[k - 1][step_right[k - 1][i]];
        }
    }


    auto solve_r = [&] (int a, int b){
        int idx = b;
        int answer = 0;

        for(int k = 21 ; k >= 0; k--){
            ll nxt = step_right[k][idx];
            if (nxt >= a) continue;
            else{
                answer += sum_right[k][idx];
                idx = step_right[k][idx];
            }
        }

        int ultimo_derecha = r[idx] == -1 ? n - 1 : r[idx];
        answer += (ultimo_derecha - idx) * h[idx];

        return answer;
    };

    auto solve_l = [&] (int a, int b){
        int idx = b - 1;
        int answer = 0;

        for(int k = 21; k >= 0; k--){
            ll nxt = step_left[k][idx];
            if (nxt < a) continue;
            else{
                answer += sum_left[k][idx];
                idx = step_left[k][idx];
            }
        }

        int ultimo_izquierda = l[idx];
        answer += (idx - ultimo_izquierda ) * h[idx];

        return answer;
    };

    int q; cin >> q;
    for(int i = 0 ; i < q ; ++ i){
        int a, b;
        cin >> a >> b;
        a-- ; b-- ;
        if(a > b) cout << solve_r(a, b) << "\n";
        else cout << solve_l(a, b) << "\n";
    }
}
