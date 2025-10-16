typedef long long ll;

const int INF = 1e9;
const ll LLINF = 4e18;

long double area(vector<pair<long double, long double>> &cords) {
  int n = (int)cords.size();
  long double area = 0;
  for (int i = 0; i < n; i++) {
    long double x1 = cords[i].first, y1 = cords[i].second;
    long double x2 = cords[(i + 1) % n].first, y2 = cords[(i + 1) % n].second;
    //cout <<  ((x1 * y2) - (y1 * x2)) << "\n";
    area += ((x1 * y2) - (y1 * x2));
  }

  return abs(area) / 2;
}

void solve() {
   int n; cin >> n;
   vector<pair<long double, long double>> cords(n);
   for (int i = 0; i < n; i++) {
     cin >> cords[i].first >> cords[i].second;
   }
   long double aT = area(cords);
   //cout << "at = " << aT << "\n";
   long double minA = LDBL_MAX;
   for (int i = 0; i < n; i++) {
     pair<long double, long double> cur = cords[i];
     vector<pair<long double, long double>> p1;
     p1.push_back(cur);
     p1.push_back(cords[(i + 1) % n]);
     for (int j = i + 2; j <= (i + n - 2); j++) {
       p1.push_back(cords[j % n]);
       long double curArea = area(p1);
       minA = min(minA, abs((aT - curArea) - curArea));
     }
   }
   printf("%.1Lf\n", minA);
}

int32_t main() {
  int t = 1;
  while (t--) {
    solve();
  }
}
