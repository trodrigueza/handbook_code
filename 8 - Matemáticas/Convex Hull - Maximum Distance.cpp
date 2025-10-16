// O(nlogn)
typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e9;
const ll LLINF = 4e18;

struct Point {
  int x, y;
  bool operator<(const Point& p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator==(const Point& p) const {
    return tie(x, y) == tie(p.x, p.y);
  }
};

ll dist2(const Point& a, const Point& b) {
  ll dx = a.x - b.x;
  ll dy = a.y - b.y;
  return dx * dx + dy * dy;
}

vector<Point> convexHull(vector<Point>& points) {
  int n = points.size();
  sort(points.begin(), points.end());
  points.erase(unique(points.begin(), points.end()), points.end());
  n = points.size();

  if (n < 2) return points;

  vector<Point> hull(2*n);
  int k = 0;

  for (int i = 0; i < n; ++i) {
    while (k >= 2 && (hull[k-1].x - hull[k-2].x) * (points[i].y - hull[k-2].y) - (hull[k-1].y - hull[k-2].y) * (points[i].x - hull[k-2].x) <= 0) k--;
    hull[k++] = points[i];
  }

  for (int i = n-2, t = k+1; i >= 0; --i) {
    while (k >= t && (hull[k-1].x - hull[k-2].x) * (points[i].y - hull[k-2].y) - (hull[k-1].y - hull[k-2].y) * (points[i].x - hull[k-2].x) <= 0) k--;
    hull[k++] = points[i];
  }

  hull.resize(k-1);
  return hull;
}

void solve() {
  int n; cin >> n;
  vector<Point> points(n);
  for (int i = 0; i < n; i++) {
    cin >> points[i].x;
  }
  for (int i = 0; i < n; i++) {
    cin >> points[i].y;
  }

  auto hull = convexHull(points);
  int m = hull.size();

  if (m == 1) {
    cout << 0 << "\n";
    return;
  }

  ll maxDist2 = 0;

  for (int i = 0, j = 1; i < m; i++) {
    while (dist2(hull[i], hull[(j+1) % m]) > dist2(hull[i], hull[j])) {
      j = (j + 1) % m;
    }
    maxDist2 = max(maxDist2, dist2(hull[i], hull[j]));
  }

  cout << maxDist2 << "\n";
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  while (t--) {
    solve();
  }
}
