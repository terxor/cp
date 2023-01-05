template <typename T, T (*Combine) (T, T), void (*LeafUpdate) (T&, T)>
struct SegmentTree {
private:
  vector<T> s;
  T default_value;
  vector<int> l, r;
  int n, k = 0, start;
  int ql, qr;
  inline bool out_range (int z) { return (ql > r[z] || qr < l[z]); }
  inline bool in_range (int z) { return (ql <= l[z] && r[z] <= qr); }
  void pull (int z) { s[z] = Combine(s[2 * z], s[2 * z + 1]); }
  void build() {
    for (int i = start - 1; i >= 1; i--) {
      pull(i); l[i] = l[2 * i]; r[i] = r[2 * i + 1];
    }
  }
  T query (int z) {
    if (in_range(z)) return s[z];
    if (out_range(z)) return default_value;
    return Combine(query(2 * z), query(2 * z + 1));
  }
public:
  SegmentTree (const vector<T>& a, T default_value) {
    this->default_value = default_value;
    n = (int)a.size();
    while ((1 << k) < n) k++;
    start = (1 << k);
    s.assign(2 * start, default_value);
    l.assign(2 * start, 0);
    r.assign(2 * start, 0);
    for (int i = 0; i < start; i++) {
      if (i < n) s[start + i] = a[i];
      l[start + i] = r[start + i] = i;
    }
    build();
  }
  T query (int lf, int rt) {
    ql = lf; qr = rt; return query(1);
  }
  void update (int i, T x) {
    int z = start + i;
    LeafUpdate(s[z], x);
    while (z / 2) { z /= 2; pull(z); }
  }
};
