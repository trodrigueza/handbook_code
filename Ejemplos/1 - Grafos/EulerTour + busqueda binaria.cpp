German had always dreamed of joining the legendary tech company known as Infinite Compilation, Perpetual Confusion (ICPC). It was a company surrounded by mystery and challenge, where logic was king and only the brightest minds could find their place.
One day, German discovered something unusual about how the company worked. Every employee reported to exactly one other person, except for the CEO, who stood at the very top and had employee ID 1. From the CEO down, each person could have multiple people working under them, forming a giant organizational chart that branched out in every direction.
To join the company, German didn't need to submit a resume or pass a technical test. Instead, there was a unique challenge: he had to answer a series of questions about how the employees were organized and what they knew.
Each employee at ICPC was an expert in one specific topic. The questions German would face went something like this: "For a given employee x, how many people under their supervision—including themselves—know a specific topic k?"
His friend Sebastian, who had once tried to join ICPC, remembered these questions clearly. Before he was caught snooping through the company's systems, he managed to get a copy of the entire employee structure—who reports to whom—and the exact list of questions German would be asked.
Unfortunately, Sebastian was discovered before he could find and share the answers.
Now it's up to you to help German. With the structure and questions in hand, he just needs the correct answers so he can memorize them before his interview.
Will you help him prepare and finally enter the world of Infinite Compilation, Perpetual Confusion?

vector<vector<int>> adj;
vector<int> topics;
vector<int> start;
vector<int> endT;
vector<int> ftopics;
map<int, vector<int>> tpositions;

int timer;

void dfs(int u, int p) 
{
  start[u] = timer;
  ftopics[timer] = topics[u];
  timer++;

  for (int v : adj[u]) 
    if (v != p) dfs(v, u);

  endT[u] = timer - 1;
}

void solve() 
{
  int n, q; cin >> n >> q;
  adj.assign(n + 1, {});
  topics.resize(n + 1);
  start.resize(n + 1);
  endT.resize(n + 1);
  ftopics.resize(n);
  tpositions.clear();

  for (int i = 1; i <= n; i++) cin >> topics[i];
  for (int i = 0; i < n - 1; ++i) {
    int from, to; cin >> from >> to;
    adj[from].push_back(to);
    adj[to].push_back(from);
  }

  timer = 0;
  dfs(1, 0);

  for (int i = 0; i < n; i++) {
    tpositions[ftopics[i]].push_back(i);
  }

  for (int i = 0; i < q; ++i) {
    int x, k; cin >> x >> k;

    if (tpositions.find(k) == tpositions.end()) {
      cout << 0 << '\n';
      continue;
    }

    auto& positions = tpositions[k];

    auto it_start = lower_bound(positions.begin(), positions.end(), start[x]);
    auto it_end = upper_bound(positions.begin(), positions.end(), endT[x]);

    int count = distance(it_start, it_end);
    cout << count << '\n';
  }
} 

