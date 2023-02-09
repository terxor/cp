#include <bits/stdc++.h>
using namespace std;
namespace cptemplate { // {{{
using Long = long long;
using ii = pair<int, int>;
using ll = pair<Long, Long>;
using vi = vector<int>;
using vii = vector<ii>;
using vl = vector<Long>;
using vll = vector<ll>;
using vs = vector<string>;

#ifdef LOCAL
#include <debug.hh>
#else
#define dbg(...) ;
#endif

#define MACRO4(_1,_2,_3,_4,NAME,...) NAME
#define rep_0(b) for (int _loopvar = 0; _loopvar < int(b); _loopvar++)
#define rep_1(i, b) for (int i = 0; i < int(b); i++)
#define rep_2(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep_3(i, a, b, s) for (int i = int(a); i < int(b); i += int(s))
#define rep(...) MACRO4(__VA_ARGS__,rep_3,rep_2,rep_1,rep_0)(__VA_ARGS__)
#define per_1(i, b) for (int i = int(b) - 1; i >= 0; i--)
#define per_2(i, a, b) for (int i = int(b) - 1; i >= int(a); i--)
#define per_3(i, a, b, s) for (int i = int(b) - 1; i >= int(a); i -= int(s))
#define per(...) MACRO4(__VA_ARGS__,per_3,per_2,per_1)(__VA_ARGS__)
#define iter_1(a, v) for (auto& a : (v))
#define iter_2(a, b, v) for (auto& [a, b] : (v))
#define iter_3(a, b, c, v) for (auto& [a, b, c] : (v))
#define iter(...) MACRO4(__VA_ARGS__,iter_3,iter_2,iter_1)(__VA_ARGS__)

#define pb push_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define lb(x, v) distance(begin(v), lower_bound(all(v), x))
#define ub(x, v) distance(begin(v), upper_bound(all(v), x))
#define tests int _tc; input(_tc); while (_tc--)
#define perm(v) for (bool _flag = true; exchange(_flag, false) or next_permutation(all(v));)

template<typename T> bool ckmin (T& a, const T& b) { return (b < a ? a = b, true : false); }
template<typename T> bool ckmax (T& a, const T& b) { return (b > a ? a = b, true : false); }
template<typename T> int len (const T& t) { return t.size(); }
template<typename T> T sum (const vector<T>& v) { return accumulate(all(v), 0); }
template<typename T> T min (const vector<T>& v) { return *min_element(all(v)); }
template<typename T> T max (const vector<T>& v) { return *max_element(all(v)); }
template<typename T> T sorted (const T& v, bool reverse = false) { auto u = v; if (reverse) sort(rall(v)); else sort(all(v)); return u; }
template<typename T> T reversed (const T& v) { auto u = v; reverse(all(u)); return u; }
template<typename T> void make_unique (vector<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
template<typename T> vector<T> range (T l, T r, T step = 1) {
  if (r < l) step *= -1;
  vector<T> res;
  for (T i = l; (r < l ? i >= r : i <= r); i += step) res.push_back(i);
  return res;
}
template<typename T> vector<int> sorted_index (const vector<T>& t) {
  vector<int> v = range(0, len(t) - 1);
  sort(all(v), [&] (int i, int j) { return t[i] < t[j]; });
  return v;
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
template<typename U> void print(vector<U> container, char sep = ' ') {
  for (int i = 0; i < len(container); i++) {
    cout << container[i];
    if (i < len(container) - 1) cout << sep;
  }
  print();
}
template<typename U, typename... V> void print (const U& u, const V& ...v) {
  cout << u;
  if (sizeof...(v)) cout << ' ';
  print(v...);
}

template<typename T> void input (vector<T>& container) {
  for (auto& x : container) cin >> x;
}
template<typename U, typename V> void input (pair<U, V> p) {
  cin >> p.first >> p.second;
}
template<typename T> void input (T& t) { cin >> t; }
void read() {}
template<typename U, typename ...V> void read (U& u, V& ...v) {
  input(u); read(v...);
}

struct fast_io {
  fast_io() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(11);
  }
} _fast_io;
}
using namespace cptemplate; // }}}

int main() {
}
