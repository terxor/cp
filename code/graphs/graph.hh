namespace graph_alg {
vector<vector<int>> scc (const vector<vector<int>>& adj) {
  int n = int(adj.size()), cur = 0;
  vector<int> vis(n, 0), seq(n), st;
  vector<vector<int>> res;
  function<int(int)> dfs = [&] (int u) {
    vis[u] = 1;
    seq[u] = cur++;
    st.push_back(u);
    int low = seq[u];
    for (int v : adj[u]) {
      if (vis[v] == 1) low = min(low, seq[v]);
      else if (vis[v] == 0) {
        low = min(low, dfs(v));
      }
    }
    if (low == seq[u]) {
      vector<int> c;
      while (c.empty() || c.back() != u) {
        int v = st.back(); st.pop_back();
        seq[v] = n + 1;
        c.push_back(v);
      }
      reverse(c.begin(), c.end());
      res.push_back(c);
    }
    return low;
  };
  for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
  return res;
}

vector<vector<int>> scc_dag (const vector<vector<int>>& scc_list, const vector<vector<int>>& adj_orig) {
  int n = adj_orig.size(), k = scc_list.size();
  vector<int> root(n);
  unordered_map<int, int> root_id;
  for (int i = 0; i < k; i++) {
    int r = scc_list[i][0];
    root_id[r] = i;
    for (auto v : scc_list[i]) root[v] = r;
  }
  vector<vector<int>> adj(k);
  for (int u = 0; u < n; u++) {
    int u1 = root[u];
    for (int v : adj_orig[u]) {
      int v1 = root[v];
      if (u1 == v1) continue;
      adj[root_id[u1]].push_back(root_id[v1]);
    }
  }
  return adj;
}

int dag_source (const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<int> inc(n, 0), vis(n, 0);
  for (int i = 0; i < n; i++) {
    for (int v : adj[i]) inc[v]++;
  }
  function<int(int)> dfs = [&] (int u) {
    int cnt = 1;
    vis[u] = 1;
    for (int v : adj[u]) if (!vis[v]) cnt += dfs(v);
    return cnt;
  };
  for (int i = 0; i < n; i++) if (inc[i] == 0) {
    return dfs(i) == n ? i : -1;
  }
  return -1;
}
}