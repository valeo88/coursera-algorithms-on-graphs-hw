#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(vector<int>& visited, const vector<vector<int>>& adj, int v) {
    //std::cout << "vertex v: " << v << "\n";
    visited[v]++;
    for (int w : adj[v]) {
        if (visited[w] == 0) {
            explore(visited, adj, w);
        } else {
            visited[w]++;
        }
    }

}

int acyclic(vector<vector<int>> &adj) {
  //write your code here
  for (int v = 0; v < adj.size(); ++v) {
    vector<int> visited(adj.size(),0);
    explore(visited,adj,v);
    if (visited[v] > 1) {
        return 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
