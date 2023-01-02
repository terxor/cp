/* max clique size calculator for small graph (n <= 20) */
struct clq_small {
  vector<int> f;
  int n;

  clq_small (vector<int> adj) {
    n = (int)adj.size();
    f.assign(1 << n, 0);
    for (int b = 1; b < (1 << n); b++) {
      int k = 0, x = b; /* k = bit count */
      while (x) {
        int z = (x & (~(x - 1)));
        f[b] = max(f[b], f[b ^ z]); /* max clq without this vtx */
        x ^= z;
        k++;
      }
      int u = 0;
      while (!(b & (1 << u))) u++;
      x = (b ^ (1 << u)); /* now check if vtx set 'b' is clique */
      if (f[x] == k - 1 && (b & adj[u]) == x) f[b] = k;
    }
  }

  /* get max clique size from subset of vertices */
  int get (int s) {
    assert(0 <= s && s < (1 << n));
    return f[s];
  }
};

struct clq {
  vector<clq_small> c;
  vector<int> g; /* compatible set of vtx in second graph wrt set in first graph */
  int n1, n2;

  clq (vector<Long> adj) {
    int n = (int)adj.size();
    assert(n > 1);
    n1 = n / 2;
    n2 = n - n1;
    vector<int> adj1(n1), adj2(n2);
    for (int i = 0; i < n1; i++) adj1[i] = adj[i] & ((1LL << n1) - 1);
    for (int i = 0; i < n2; i++) adj2[i] = (adj[i + n1] >> n1);
    c = vector<clq_small> { clq_small(adj1), clq_small(adj2) };
    g.assign(1 << n1, 0);
    for (int b = 0; b < (1 << n1); b++) {
      g[b] = 0;
      for (int u = 0; u < n2; u++) {
        if ((b & adj[u + n1]) == b) g[b] |= (1 << u);
      }
    }
  }

  int max_size() {
    int ans = 0;
    for (int b = 0; b < (1 << n1); b++) {
      ans = max(ans, c[0].get(b) + c[1].get(g[b]));
    }
    return ans;
  }
};
