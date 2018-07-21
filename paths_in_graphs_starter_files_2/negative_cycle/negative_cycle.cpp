#include <iostream>
#include <vector>
#include <limits>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  // use Bellman-Ford algorithm
  const int inf = std::numeric_limits<int>::max();
  // use long long to prevent int overflow
  vector<long long> dist(adj.size(),inf);
  // let initial s = 0
  dist[0] = 0;
  // repeate |V| - 1 times
  for (int m = 0; m < adj.size() - 1; ++m) {
      for (int s = 0; s < adj.size(); ++s) {
        for (int j = 0; j < adj[s].size(); ++j) {
            const int v = adj[s][j];
            if (dist[v] > dist[s] + cost[s][j]) {
                dist[v] = dist[s] + cost[s][j];
            }
        }
      }
  }
  // check |V|th iteration
  for (int s = 0; s < adj.size(); ++s) {
    for (int j = 0; j < adj[s].size(); ++j) {
        const int v = adj[s][j];
        if (dist[v] > dist[s] + cost[s][j]) {
            return 1;
        }
    }
  }

  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
