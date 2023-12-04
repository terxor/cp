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
/*========================================*/
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b - 1); i >= (a); i--)
#define R0F(i, a) ROF(i, 0, a)
#define F0R(i, a) FOR(i, 0, a) 
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(a) (int)(a).size()
#define pb push_back
#define mp make_pair
#define rsz resize
#define s second
#define f first
using ld = long double;
using vd = vector<ld>;
using vi = vector<int>;
const ll MOD = (ll)1e9 + 7;
const int INF = (int)1e9 + 1;
template<typename T>
bool ckmax (T& a, T b) { return (b > a) ? a = b, 1 : 0; }
template<typename T>
bool ckmin (T& a, T b) { return (b < a) ? a = b, 1 : 0; }
/* --- */
/* 1D range update, range query */
template<class T, int SZ> struct LazySeg { // set SZ to a power of 2
	T sum[2*SZ], lazy[2*SZ];
	LazySeg() {
		memset(sum,0,sizeof sum);
		memset(lazy,0,sizeof lazy);
	}
	void push(int ind, int L, int R) { // modify values for current node
		sum[ind] += lazy[ind];
		if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
		lazy[ind] = 0; // pushed lazy to children
	}
	void pull(int ind) { // recalc values for current node
			sum[ind] = max(sum[2*ind], sum[2*ind+1]); }
	void build() { ROF(i,1,SZ) pull(i); }
	void upd(int lo, int hi, T inc, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc;
			push(ind,L,R); return;
		}
		int M = (L+R)/2;
		upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
		pull(ind);
	}
	T qsum(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
		push(ind,L,R);
		if (lo > R || L > hi) return -INF;
		if (lo <= L && R <= hi) return sum[ind];
		int M = (L+R)/2;
		return max(qsum(lo,hi,2*ind,L,M), qsum(lo,hi,2*ind+1,M+1,R));
	}
};
/* HLD
 * Description: Heavy-Light Decomposition, add val to verts
 * and query sum in path/subtree
 * Time: any tree path is split into $O(\log N)$ parts */
template<int SZ, bool VALS_IN_EDGES> struct HLD {
	int N; vi adj[SZ];
	int par[SZ], sz[SZ], depth[SZ];
	int root[SZ], pos[SZ]; vi rpos;
	int itr;
	void addEdge(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
	void dfsSz(int v = 1) {
		if (par[v]) adj[v].erase(find(all(adj[v]),par[v]));
		sz[v] = 1;
		trav(u,adj[v]) {
			par[u] = v; depth[u] = depth[v]+1;
			dfsSz(u); sz[v] += sz[u];
			if (sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v = 1) {
		pos[v] = itr++; rpos.pb(v);
		trav(u,adj[v]) {
			root[u] = (u == adj[v][0] ? root[v] : u);
			dfsHld(u);
		}
	}
	void init(int _N) {
		N = _N; par[1] = depth[1] = 0; root[1] = 1;
		itr = 0;
		dfsSz(); dfsHld();
	}
	LazySeg<ll,SZ> tree;
	template <class BinaryOp>
		void processPath(int u, int v, BinaryOp op) {
			for (; root[u] != root[v]; v = par[root[v]]) {
				if (depth[root[u]] > depth[root[v]]) swap(u, v);
				op(pos[root[v]], pos[v]);
			}
			if (depth[u] > depth[v]) swap(u, v);
			op(pos[u]+VALS_IN_EDGES, pos[v]);
		}
	void modifyPath(int u, int v, int val) {
		processPath(u, v, [this, &val](int l, int r) {
				tree.upd(l, r, val); });
	}
	void modifySubtree(int v, int val) {
		tree.upd(pos[v]+VALS_IN_EDGES,pos[v]+sz[v]-1,val);
	}
	ll queryPath(int u, int v) {
		if (u == v) return 0;
		ll res = -INF; 
		processPath(u, v, [this, &res](int l, int r) { 
				res = max(res, tree.qsum(l, r)); 
			});
		return res;
	}
};


char buf[100];
string getString() {
	scanf("%s", buf);
	return string(buf);
}

const int SZ = (1 << 14);
int main() {	
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		HLD<SZ, 1> hld;
		int n, q, a, b, x, y, z;
		scanf("%d", &n);
		vector<ii> edges (n + 1);
		vector<int> cost (n + 1);
		for (int i = 1; i <= n - 1; i++) {
			scanf("%d%d%d", &x, &y, &z);
			edges[i] = ii(x, y); 
			cost[i] = z;
			hld.addEdge(x, y);
		}
		hld.init(n);
		for (int i = 1; i <= n - 1; i++)
			hld.modifyPath(edges[i].f, edges[i].s, cost[i]);
		scanf("%d", &q);
		string tp;
		while ((tp = getString()) != "DONE") {
			scanf("%d%d", &a, &b);
			if (tp == "QUERY") printf("%lld\n", hld.queryPath(a, b));
			else {
				int prev = hld.queryPath(edges[a].f, edges[a].s);
				hld.modifyPath(edges[a].f, edges[a].s, b - prev);
			}
		}
	}
}
