int R[] = {0, 0, 1, -1}, L[] = {1, -1, 0, 0};

int cal(vector<int>& arr) 
{
  int best = 0, act = 0;
  for (int x : arr) {
    act = max(0LL, act + x);
    best = max(best, act);
  }
  return best;
}

vector<int> spiral(vector<vector<int>>& mat) 
{
  int n = mat.size();
  int top = 0, bottom = n - 1, left = 0, right = n - 1;
  vector<int> res; res.reserve(n * n);

  while (top <= bottom && left <= right) {
    for (int j = left; j <= right; j++) {
      res.push_back(mat[top][j]);
    }
    top++;
    for (int i = top; i <= bottom; i++) {
      res.push_back(mat[i][right]);
    }
    right--;
    if (top <= bottom) {
      for (int j = right; j >= left; j--) {
	res.push_back(mat[bottom][j]);
      } 
      bottom--;
    }
    if (left <= right) {
      for (int i = bottom; i >= top; i--) {
	res.push_back(mat[i][left]);
      }
      left++;
    }
  }
  return res;
}

vector<vector<int>> rot90(vector<vector<int>>& mat) 
{
  int n = mat.size();
  vector<vector<int>> res(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[j][n - 1 - i] = mat[i][j];
    }
  }
  return res;
}

vector<vector<int>> rot180(vector<vector<int>>& mat) 
{
  int n = mat.size();
  vector<vector<int>> res(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[n - 1 - i][n - 1 - j] = mat[i][j];
    }
  }
  return res;
}

vector<vector<int>> rot270(vector<vector<int>> &mat) 
{
  int n = mat.size();
  vector<vector<int>> res(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[n - 1 - j][i] = mat[i][j];
    }
  }
  return res;
}

vector<vector<int>> reflection(vector<vector<int>> &mat) 
{
  vector<vector<int>> res = mat;
  for (int i = 0; i < mat.size(); i++) {
    reverse(res[i].begin(), res[i].end());
  }
  return res;
}


void solve()
{
  int n; cin >> n;
  vector<vector<int>> v(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> v[i][j];
  }

  int res = 0;

  vector<vector<vector<int>>> mats;
  mats.push_back(v);
  mats.push_back(rot90(v));
  mats.push_back(rot180(v));
  mats.push_back(rot270(v));

  for (auto& m : mats) {
    auto v1 = spiral(m);
    res = max(res, cal(v1));

    auto mr = reflection(m);
    auto v2 = spiral(mr);
    res = max(res, cal(v2));
  }

  cout << res << "\n";
}
