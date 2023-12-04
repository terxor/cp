/*
   Tested on:
	https://www.spoj.com/problems/LCA/
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <bitset>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef XVENOM
	#define errp(...) fprintf(stderr, __VA_ARGS__)
	#define dbg(...) errp("[%s]: ", #__VA_ARGS__), dbg_str(__VA_ARGS__)
#else
	#define errp(...)
	#define dbg(...)
#endif
template <typename U, typename V> string to_string (pair<U, V>);
string to_string (const string& e_) { return "\"" + e_ + "\""; }
string to_string (char e_) { return "\'" + string(1, e_) + "\'"; }
string to_string (bool e_) { return e_ ? "true" : "false"; }
template <typename T> string to_string (T e_) {
	string s_ = "[ ";
	for (const auto& x_ : e_) s_ += to_string(x_) + " ";
	return s_ + "]";
}
template <typename U, typename V> string to_string (pair<U, V> e_) {
	return "(" + to_string(e_.first) + ", " + to_string(e_.second) + ")";
}
void dbg_str () { errp(" \n"); }
template <typename U, typename... V> void dbg_str (U u, V... v) {
 	errp(" %s", to_string(u).c_str()); dbg_str(v...);
}
/* --- */
/* Func is an associative function */
template<typename T> class SparseTable {
	vector<vector<T>> v;
	int n, k;
	public:
	SparseTable () { }
	T func (T a, T b) { return min(a, b); }
	void init (const vector<T>& a) {
		n = (int)a.size();
		k = 0;
		while ((1 << k) <= n) k++;
		v.assign(k, vector<T> (n));
		for (int i = 0; i < n; i++) v[0][i] = a[i];
		for (int j = 1; j < k; j++)
			for (int i = 0; i < n - (1 << j) + 1; i++)
				v[j][i] = func(v[j - 1][i], v[j - 1][i + (1 << (j - 1))]);
	}
	T query (int i, int j) {
		int p = 31 - __builtin_clz(j - i + 1);
		return func(v[p][i], v[p][j - (1 << p) + 1]);
	}
};

struct LCA {
	vector<vector<int>> adj;
	vector<int> depth, pos; 
	vector<ii> tmp;
	SparseTable<ii> st;

	LCA(int n) {
		depth.assign(n, 0);
		pos.assign(n, 0);
		adj.assign(n, vector<int>(0));
	}
	void addEdge (int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void dfs (int u, int p) {
		pos[u] = (int)tmp.size();
		tmp.push_back({depth[u], u});
		for (int v : adj[u]) if (v != p) {
			depth[v] = depth[u] + 1; dfs(v, u);
			tmp.push_back({depth[u], u});
		}
	}
	void init () {
		depth[0] = 0; dfs(0, -1); st.init(tmp);
	}
	int query (int u, int v) {
		if (pos[u] > pos[v]) swap(u, v);
		return st.query(pos[u], pos[v]).second;
	}
};


int main() {
	int n, x, y, q, cn = 1;
	scanf("%d", &n);
	LCA lca(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		while (x--) {
			scanf("%d", &y);
			lca.addEdge(i, y);
		}
	}
	lca.init();
	scanf("%d", &q);
//		printf("Case %d:\n", cn++);
	while (q--) {
		scanf("%d%d", &x, &y);
		printf("%d\n", lca.query(x, y));
	}
}


