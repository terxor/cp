#include <bits/stdc++.h>
using namespace std;
using Long = long long;
using ii = pair<int, int>;
using ll = pair<Long, Long>;

#ifdef LOCAL
#include <debug.hh>
#else
#define dbg(...) ;
#endif

#define ALL(x) begin(x), end(x)

template<typename T> int len (const T& t) { return t.size(); }

template<typename T> vector<T> sorted (const vector<T>& v, bool reverse = false) {
  auto u = v;
  if (reverse) sort(u.rbegin(), u.rend());
  else sort(u.begin(), u.end());
  return u;
}

template<typename T> vector<T> reversed (const vector<T>& v) {
  auto u = v;
  reverse(v.begin(), v.end());
  return u;
}

template<typename T> vector<pair<T, int>> grouped (const vector<T>& v) {
  vector<pair<T, int>> res;
  for (auto& e : v) {
    if (res.empty() or res.back().first != e) res.push_back({e, 1});
    else res.back().second++;
  }
  return res;
}

void print() { cout << '\n'; }
template<typename U, typename... V> void print (const U& u, const V& ...v) {
  cout << u;
  if (sizeof...(v)) cout << ' ';
  print(v...);
}

template<typename U> void printList(U container, char sep = ' ') {
  int s = len(container);
  for (auto& e : container) cout << e << (--s ? sep : '\n');
}

template<typename T> vector<vector<T>> vec2D (int n = 0, int m = 0, int default_value = 0) {
  return vector<vector<T>>(n, vector<T>(m, default_value));
}

void input() {}
template<typename U, typename ...V> void input (U& u, V& ...v) {
  cin >> u; input(v...);
}

template<typename T> void inputList (vector<T>& container) {
  for (auto& x : container) cin >> x;
}

struct Setup_io {
    Setup_io() {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
        cout << fixed << setprecision(11);
    }
} setup_io;

/* --- */

int main() {
}
