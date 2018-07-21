#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  // use Bellman-Ford algorithm
  vector<int> prev(adj.size(), -1);
  distance[s] = 0;
  reachable[s] = 1;
  // repeate |V| - 1 times
  for (int m = 0; m < adj.size() - 1; ++m) {
      for (int s = 0; s < adj.size(); ++s) {
        for (int j = 0; j < adj[s].size(); ++j) {
            const int v = adj[s][j];
            reachable[v] = 1;
            if (distance[v] > distance[s] + cost[s][j]) {
                distance[v] = distance[s] + cost[s][j];
                prev[v] = s;
            }
        }
      }
  }
  vector<int> neg_cycle_nodes;
  // check |V|th iteration
  for (int s = 0; s < adj.size(); ++s) {
    for (int j = 0; j < adj[s].size(); ++j) {
        const int v = adj[s][j];
        if (distance[v] > distance[s] + cost[s][j]) {
            neg_cycle_nodes.push_back(v);
        }
    }
  }
  // mark all nodes in negative cycle
  for (int v : neg_cycle_nodes) {
    shortest[v] = 0;
    int x = prev[v];
    while(x!=-1 && x!=v) {
        shortest[x] = 0;
        x = prev[x];
    }
  }

}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<int>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
