#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

void explore(vector<bool>& visited, vector<int>& cc_num, const vector<vector<int>>& adj, int v, int cc) {
    visited[v] = true;
    cc_num[v] = cc;
    for (int w : adj[v]) {
        if (!visited[w]) {
            explore(visited, cc_num, adj, w, cc);
        }
    }
}

int number_of_components(vector<vector<int> > &adj) {
  vector<bool> visited(adj.size(), false);
  vector<int> cc_num(adj.size(), 0);
  int cc = 1;
  for (int v = 0; v < adj.size(); ++v) {
    if (!visited[v]) {
        explore(visited, cc_num, adj, v, cc);
        cc++;
    }
  }
  auto max_it = std::max_element(cc_num.begin(), cc_num.end());
  return max_it!=cc_num.end() ? *max_it : 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
