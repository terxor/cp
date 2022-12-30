struct SegmentTree {
private:
  vector<int> s, l, r;
  int n, k = 0, start;
  int ql, qr;
  inline bool out_range (int z) { return (ql > r[z] || qr < l[z]); }
  inline bool in_range (int z) { return (ql <= l[z] && r[z] <= qr); }
  int combine (int a, int b) { return a + b; }
  void pull (int z) { s[z] = combine(s[2 * z], s[2 * z + 1]); }
  void build() {
    for (int i = start - 1; i >= 1; i--) {
      pull(i); l[i] = l[2 * i]; r[i] = r[2 * i + 1];
    }
  }
  int query (int z) {
    if (in_range(z)) return s[z];
    if (out_range(z)) return 0;
    return combine(query(2 * z), query(2 * z + 1));
  }
public:
  SegmentTree (const vector<int>& a) {
    n = (int)a.size();
    while ((1 << k) < n) k++;
    start = (1 << k);
    s.assign(2 * start, 0);
    l.assign(2 * start, 0);
    r.assign(2 * start, 0);
    for (int i = 0; i < start; i++) {
      s[start + i] = (i < n ? a[i] : 0);
      l[start + i] = r[start + i] = i;
    }
    build();
  }
  int query (int lf, int rt) {
    ql = lf; qr = rt; return query(1);
  }
  void update (int i, int x) {
    int z = start + i;
    s[z] += x;
    while (z / 2) { z /= 2; pull(z); }
  }
};

