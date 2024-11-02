#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;

vvl B(10, vl(10));
vl P{0, 5, 5, 5, 5, 5};

ll ans = 100;
bool CanPut(ll y, ll x, ll p) {
  for (auto i = y; i < y + p; ++i) {
    if (10 <= i) return false;
    for (auto j = x; j < x + p; ++j) {
      if (10 <= j) return false;

      if (B[i][j] == 0) return false;
    }
  }

  return true;
}

void Put(ll y, ll x, ll p, ll v) {
  for (auto i = y; i < y + p; ++i) {
    for (auto j = x; j < x + p; ++j) {
      B[i][j] = v;
    }
  }
}

void solve(ll ret) {
  if (ans < ret) return;

  auto all_zero = true;
  for (auto i = 0; all_zero && i < 10; ++i) {
    for (auto j = 0; all_zero && j < 10; ++j) {
      if (B[i][j] == 1) {
        all_zero = false;
        break;
      }
    }
  }

  if (all_zero) {
    ans = min(ans, ret);
    return;
  }

  for (auto i = 0; i < 10; ++i) {
    for (auto j = 0; j < 10; ++j) {
      if (B[i][j] == 0) continue;

      for (auto p = 5; 1 <= p; --p) {
        if (P[p] < 1) continue;

        if (!CanPut(i, j, p)) continue;

        P[p] -= 1;
        Put(i, j, p, 0);

        solve(ret + 1);

        P[p] += 1;
        Put(i, j, p, 1);
      }

      return;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  for (auto&& r : B) {
    for (auto&& b : r) {
      cin >> b;
    }
  }

  solve(0);

  if (ans == 100) {
    cout << -1;
    return 0;
  }

  cout << ans;

  return 0;
}