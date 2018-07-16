#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

bool color(vector<vector<int> > &adj, int s) {
  //write your code here
  const size_t n = adj.size();
  const size_t inf = n + 1;
  vector<int> dist(n, inf);
  vector<bool> white(n, false);
  dist[s] = 0;
  white[s] = true;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
        if (dist[v] == inf) {
            q.push(v);
            dist[v] = dist[u] + 1;
            white[v] = !white[u];
        } else {
            if (white[u] == white[v]) {
                return false;
            }
        }
    }
  }
  return true;
}

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  return color(adj, 0) ? 1 : 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
