const int N = 2e8;
bool nums[N + 1];

int32_t main() {
  int n; cin >> n;

  memset(nums, true, sizeof(nums));

  for (int i = 2; i*i <= n; i++) {
    if (nums[i]) {
      for (int j = i*i; j <= n; j += i) {
        nums[j] = false;
      }
    }
  }
  // nums[i] == 1 iff isPrime(i)
}
