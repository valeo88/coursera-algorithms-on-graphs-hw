#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  const int inf = std::numeric_limits<int>::max();
  // use long long to prevent int overflow
  vector<long long> dist(adj.size(),inf);
  dist[s] = 0;
  // comparator of pairs for min-heap
  auto compare = [](const pair<int,int>& lhs, const pair<int,int>& rhs) {
    return lhs.second > rhs.second;
  };
  // first - vertex, second - dist value
  priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(compare)> h(compare);
  for (int i = 0; i < dist.size(); ++i) {
    h.push(std::make_pair(i, dist[i]));
  }
  while (!h.empty()) {
    pair<int,int> u = h.top();
    h.pop();
    for (int j = 0; j < adj[u.first].size(); ++j) {
        const int v = adj[u.first][j];
        if (dist[v] > dist[u.first] + cost[u.first][j]) {
            dist[v] = dist[u.first] + cost[u.first][j];
            h.push(std::make_pair(v, dist[v]));
        }
    }
  }
  return dist[t]==inf ? -1 : dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
