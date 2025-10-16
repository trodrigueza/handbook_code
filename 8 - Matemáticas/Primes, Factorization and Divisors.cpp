const int N = (int)1e7;
int lp[N+1];
vector<int> pr;

vector<pair<int, int>> factorize(int x) {
  vector<pair<int, int>> factors;
  while (x > 1) {
    int factor = lp[x];
    int count  = 0;
    while (x % factor == 0) {
      x /= factor;
      count++;
    }
    factors.push_back({factor, count});
  }
  return factors;
}

void getDivisors(int idx, long long current, const vector<pair<int, int>> &factors, vector<long long> &divisors) {
  if (idx == (int)factors.size()) {
    divisors.push_back(current);
    return;
  }
  int prime = factors[idx].first;
  int exponent = factors[idx].second;
  long long tmp = current;
  for (int i = 0; i <= exponent; i++) {
    getDivisors(idx + 1, tmp, factors, divisors);
    tmp *= prime;
  }
}

vector<long long> getAllDivisors(int x) {
  vector<pair<int, int>> factors = factorize(x);
  vector<long long> divisors;
  getDivisors(0, 1, factors, divisors);
  return divisors;
}

int32_t main() {
  for (int i = 2; i <= N; i++) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= N; j++) {
      lp[i * pr[j]] = pr[j];
      if (pr[j] == lp[i]) {
        break;
      }
    }
  }
}
