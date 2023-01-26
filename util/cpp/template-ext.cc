#include <bits/stdc++.h>
using namespace std;
namespace cptemplate {
using Long = long long;
using ii = pair<int, int>;
using ll = pair<Long, Long>;
using Vi = vector<int>;
using Vii = vector<ii>;
using Vl = vector<Long>;
using Vll = vector<ll>;
using Vs = vector<string>;

#ifdef LOCAL
#include <debug.hh>
#else
#define dbg(...) ;
#endif

#define MACRO4(_1,_2,_3,_4,NAME,...) NAME
#define FOR_0(b) for (int _loopvar = 0; _loopvar < int(b); _loopvar++)
#define FOR_1(i, b) for (int i = 0; i < int(b); i++)
#define FOR_2(i, a, b) for (int i = int(a); i < int(b); i++)
#define FOR_3(i, a, b, s) for (int i = int(a); i < int(b); i += int(s))
#define FOR(...) MACRO4(__VA_ARGS__,FOR_3,FOR_2,FOR_1,FOR_0)(__VA_ARGS__)
#define ITER_1(a, v) for (auto& a : (v))
#define ITER_2(a, b, v) for (auto& [a, b] : (v))
#define ITER_3(a, b, c, v) for (auto& [a, b, c] : (v))
#define ITER(...) MACRO4(__VA_ARGS__,ITER_3,ITER_2,ITER_1)(__VA_ARGS__)

#define PB push_back
#define LB(x, v) distance(begin(v), lower_bound(ALL(v), x))
#define ALL(x) begin(x), end(x)
#define TEST int _tc; input(_tc); while (_tc--)
#define PERM(v) for (bool _flag = true; exchange(_flag, false) or next_permutation(ALL(v));)

template<typename T> bool ckmin (T& a, const T& b) { return (b < a ? a = b, true : false); }
template<typename T> bool ckmax (T& a, const T& b) { return (b > a ? a = b, true : false); }

template<typename T> int len (const T& t) { return t.size(); }

template<typename T> T sum (const vector<T>& v) {
  return accumulate(v.begin(), v.end(), 0);
}

template<typename T> T min (const vector<T>& v) {
  return *min_element(v.begin(), v.end());
}

template<typename T> T max (const vector<T>& v) {
  return *max_element(v.begin(), v.end());
}

template<typename T> vector<T> range (T l, T r, T step = 1) {
  if (r < l) step *= -1;
  vector<T> res;
  for (T i = l; (r < l ? i >= r : i <= r); i += step) res.push_back(i);
  return res;
}

template<typename U, typename F> auto mapvec (const vector<U>& u, F f) -> vector<decltype(f(std::declval<U>()))> {
  using V = decltype(f(std::declval<U>()));
  vector<V> res;
  for (auto& e : u) res.push_back(f(e));
  return res;
}

template<typename T> T sorted (const T& v, bool reverse = false) {
  auto u = v;
  if (reverse) sort(u.rbegin(), u.rend());
  else sort(u.begin(), u.end());
  return u;
}

template<typename T> T reversed (const T& v) {
  auto u = v;
  reverse(u.begin(), u.end());
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

vector<pair<char, int>> grouped (const string& s) {
  return grouped(vector<char>(s.begin(), s.end()));
}

void print() { cout << endl; }
template<typename U, typename... V> void print (const U& u, const V& ...v) {
  cout << u;
  if (sizeof...(v)) cout << ' ';
  print(v...);
}

template<typename U> void print_list(U container, char sep = ' ') {
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

template<typename T> void input_list (vector<T>& container) {
  for (auto& x : container) cin >> x;
}

struct fast_io {
  fast_io() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(11);
  }
} _fast_io;
}
using namespace cptemplate;

int main() {
}
