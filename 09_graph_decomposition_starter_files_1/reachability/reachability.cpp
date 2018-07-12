#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<bool>& visited, const vector<vector<int> >& adj, int v, int target) {
    visited[v] = true;
    for (int w : adj[v]) {
        if (!visited[w]) {
            explore(visited, adj, w, target);
        }
    }
}


int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size());
  explore(visited,adj,x,y);
  return visited[y] ? 1 : 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
