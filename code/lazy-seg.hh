struct SegmentTree {
private:
  vector<ll> s, up;
  vector<int> l, r;
  int n, k, start;
  int ql, qr, qv;

  inline bool in_range (int z) { return (ql <= l[z] && r[z] <= qr); }
  inline bool out_range (int z) { return (ql > r[z] || qr < l[z]); }

  ll combine (ll a, ll b) { return a + b; }
  void pull (int z) { s[z] = combine(s[2 * z], s[2 * z + 1]); }
  void push (int z) {
    ll t = up[z]; up[z] = 0;
    s[z] += (r[z] - l[z] + 1) * t;
    if (z >= start) return;
    up[2 * z] += t; up[2 * z + 1] += t;
  }
  void build() {
    for (int i = start - 1; i >= 1; i--) {
      pull(i); l[i] = l[2 * i]; r[i] = r[2 * i + 1];
    }
  }
  ll query (int z) {
    push(z);
    if (in_range(z)) return s[z];
    if (out_range(z)) return 0;
    return combine(query(2 * z), query(2 * z + 1));
  }
  void update (int z) {
    push(z);
    if (in_range(z)) { up[z] += qv; push(z); return; }
    if (out_range(z)) return;
    update(2 * z); update(2 * z + 1); pull(z);
  }
public:
  SegmentTree (int _n) {
    n = _n;
    k = 0;
    while ((1 << k) < n) k++;
    start = (1 << k);
    s.assign(2 * start, 0);
    up.assign(2 * start, 0);
    l.assign(2 * start, 0);
    r.assign(2 * start, 0);
    for (int i = 0; i < start; i++) {
      l[start + i] = r[start + i] = i;
    }
    build();
  }
  ll query (int lf, int rt) {
    ql = lf; qr = rt;
    return query(1);
  }
  void update (int lf, int rt, int val) {
    ql = lf; qr = rt; qv = val;
    update(1);
  }
};
