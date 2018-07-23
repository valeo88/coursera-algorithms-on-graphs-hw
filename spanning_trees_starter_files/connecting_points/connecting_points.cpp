#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <queue>

using std::vector;
using std::pair;
using std::priority_queue;

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  // Use Prim's algorithm
  const size_t n = x.size();
  auto compare = [](const pair<int,double>& lhs, const pair<int,double>& rhs) {
    return lhs.second > rhs.second;
  };
  const double inf = std::numeric_limits<double>::max();
  vector<double> cost(n, inf);
  vector<int> parent(n,-1);
  vector<bool> in_q(n,false);
  cost[0] = 0;
  priority_queue<pair<int,double>, vector<pair<int,double>>, decltype(compare)> q(compare);
  for (int i = 0; i < n; ++i) {
    q.push(std::make_pair(i, cost[i]));
    in_q[i] = true;
  }
  while(!q.empty()) {
    pair<int,double> u = q.top();
    q.pop();
    in_q[u.first] = false;
    for (int j = 0; j < n; ++j) {
        if (u.first!=j) {
            const double d = std::sqrt((x[u.first]-x[j])*(x[u.first]-x[j]) + (y[u.first]-y[j])*(y[u.first]-y[j]));
            if (in_q[j] && cost[j] > d) {
                cost[j] = d;
                parent[j] = u.first;
                q.push(std::make_pair(j, cost[j]));
                in_q[j] = true;
            }
        }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (cost[i]!=inf) {
        result += cost[i];
    }
  }

  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
