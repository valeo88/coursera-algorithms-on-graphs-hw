#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<vector<int> > &adj, vector<bool> &visited, int x) {
  visited[x] = true;
  for (int w : adj[x]) {
    if (!visited[w]) {
        explore(adj,visited,w);
    }
  }
}

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
  used[x]++;
  for (int w : adj[x]) {
    if (used[w] == 0) {
        dfs(adj,used,order,w);
    }
  }
  order.push_back(x);
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  for (int v = 0; v < adj.size(); ++v) {
    if (used[v] == 0)
        dfs(adj,used,order,v);
  }
  std::reverse(order.begin(), order.end());
  return order;
}

int number_of_strongly_connected_components(vector<vector<int>>& adj, vector<vector<int>>& adj_r) {
  int result = 0;
  //write your code here
  vector<bool> visited(adj.size(), false);
  for (int v : toposort(adj_r)) {
    if (!visited[v]) {
        explore(adj, visited, v);
        result++;
    }
  }

  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>()); // graph G
  vector<vector<int> > adj_r(n, vector<int>()); // reverse graph Gr
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj_r[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adj_r);
}
