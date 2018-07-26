#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <set>
#include <limits>

using std::vector;
using std::pair;
using std::set;

struct Edge {
    int u;
    int v;
    double w;

    Edge(const int i, const int j, const double d) {
        u = i;
        v = j;
        w = d;
    }
};

int find_set(const vector<int>& parent, int i) {
    while (i!=parent[i]) {
        i = parent[i];
    }
    return i;
}

void union_set(vector<int>& parent, vector<int>& ranks, int i, int j) {
    int i_id = find_set(parent, i);
    int j_id = find_set(parent, j);
    if (i_id == j_id) return;
    if (ranks[i_id] > ranks[j_id]) {
        parent[j_id] = i_id;
    } else {
        parent[i_id] = j_id;
        if (ranks[i_id] == ranks[j_id]) ranks[j_id]++;
    }
}

size_t number_of_sets(const vector<int>& parent) {
    set<int> uniq(parent.begin(), parent.end());
    return uniq.size();
}

double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  // using Kruskal's alg
  const size_t n = x.size();
  vector<int> parent(n);
  vector<int> ranks(n);
  // create n sets
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
    ranks[i] = 0;
  }
  // calc weights between all points
  // create vector of edges
  vector<Edge> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
        const double d = std::sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
        edges.push_back(Edge(i,j,d));
    }
  }
  // sort edges by weight
  std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs) {
    return lhs.w < rhs.w;
  });
  //for (const Edge& e : edges) {
  //  std::cout << "u=" << e.u << " v=" << e.v << " w=" << e.w << "\n";
  //}
  if (k < n) {
      // index of edge, that not in clusters
      for (int m = 0; m < edges.size(); ++m) {
        const Edge& e = edges[m];
        if (find_set(parent, e.u)!=find_set(parent, e.v)) {
            union_set(parent, ranks, e.u, e.v);
            if (number_of_sets(parent) == k) {
                //std::cout << "outcluster_idx: " << outcluster_idx << "weight: " << edges[outcluster_idx].w << "\n";
                break;
            }

        }
      }
  }
  //for (int i = 0; i < n; ++i) {
  //  std::cout << "element: " << i << " parent: " << parent[i] << "\n";
  //}
  const double inf = std::numeric_limits<double>::max();
  double result = inf;
  for (int p = 0; p < edges.size(); ++p) {
    const Edge& e = edges[p];
    if (find_set(parent, e.u)!=find_set(parent, e.v)) {
        result = std::min(result, e.w);
    }
  }

  return result==inf ? -1 : result;
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
