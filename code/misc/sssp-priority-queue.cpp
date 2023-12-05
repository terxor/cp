/* priority queue for single source shortest path algorithm */
class sp_pq {
  const int Inf = 1e9;
  int n, num_v; /* current heap size and number of vertices*/
  vector<int> a; /* heap */
  vector<int> d; /* distances */
  vector<int> id; /* id[i] = index of vertex i in heap */

  void swap_v (int i, int j) { 
    swap(a[i], a[j]);
    id[a[i]] = i;
    id[a[j]] = j;
  }

  void heapify (int i) {
    int l = (i<<1), r = (i<<1) + 1, smallest = i;
    if (l <= n && d[a[l]] < d[a[smallest]]) smallest = l;
    if (r <= n && d[a[r]] < d[a[smallest]]) smallest = r;
    if (smallest != i) {
      swap_v(i, smallest);
      heapify(smallest);
    }
  }

  void update (int i) {
    int p = (i>>1);
    if (p && d[a[i]] < d[a[p]]) {
      swap_v(i, p);
      update(p);
    }
  }

public:
  sp_pq (int num, int start) {
    /* vertices 0...num-1 and start vertex */
    n = num_v = num;
    a.assign(n + 1, 0);
    d.assign(num_v, Inf);
    id.assign(num_v, 0);

    d[start] = 0;
    /* make heap */
    for (int i = 1; i <= n; i++) {
      a[i] = i - 1;
      id[a[i]] = i;
    }
    for (int i = n; i > 0; i--) heapify(i);
  }

  int extractMin () {
    int v = a[1];
    swap_v(1, n);
    id[v] = -1;
    n--;
    heapify(1);
    return v;
  }

  void update (int vertex, int newDist) {
    d[vertex] = newDist;
    update(id[vertex]);
  }

  vector<int> dist () {
    return d;
  }
  int dist(int i) { return d[i]; }
  int size () { return n; }
};

int shortest_path (int start, int end, vector<vector<pair<int, int>>> adj) {
  /* adjacency list should be u -> [(v1, w1), ... ] */
  int n = adj.size();
  sp_pq q = sp_pq(n, start);
  while (q.size()) {
    int u = q.extractMin();
    for (auto [v, w] : adj[u]) {
      if (q.dist(u) + w < q.dist(v)) 
        q.update(v, q.dist(u) + w);
    }
  }
  /* use q.dist() to get all shortest distances */
  return q.dist(end); 
}
