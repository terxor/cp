template <typename T, typename U, T (*Combine) (T, T), void (*NewUpdate) (U&, U), void (*ApplyUpdate) (T&, U, int) >
struct SegmentTree {
private:
  vector<T> s;
  vector<U> up;
  vector<int> l, r;
  int n, k, start;
  int ql, qr;
  T default_value;
  U qv, upd_default_value;

  inline bool in_range (int z) { return (ql <= l[z] && r[z] <= qr); }
  inline bool out_range (int z) { return (ql > r[z] || qr < l[z]); }
  void pull (int z) { s[z] = Combine(s[2 * z], s[2 * z + 1]); }
  void push (int z) {
    if (up[z] == upd_default_value) return;
    U u = up[z]; up[z] = upd_default_value;
    ApplyUpdate(s[z], u, (r[z] - l[z] + 1));
    if (z >= start) return;
    NewUpdate(up[2 * z], u); NewUpdate(up[2 * z + 1], u);
  }
  void build() {
    for (int i = start - 1; i >= 1; i--) {
      pull(i); l[i] = l[2 * i]; r[i] = r[2 * i + 1];
    }
  }
  T query (int z) {
    push(z);
    if (in_range(z)) return s[z];
    if (out_range(z)) return default_value;
    return Combine(query(2 * z), query(2 * z + 1));
  }
  void update (int z) {
    push(z);
    if (in_range(z)) { NewUpdate(up[z], qv); push(z); return; }
    if (out_range(z)) return;
    update(2 * z); update(2 * z + 1); pull(z);
  }
public:
  SegmentTree (int _n, T default_value, U upd_default_value) {
    this->default_value = default_value;
    this->upd_default_value = upd_default_value;
    n = _n;
    k = 0;
    while ((1 << k) < n) k++;
    start = (1 << k);
    s.assign(2 * start, default_value);
    up.assign(2 * start, upd_default_value);
    l.assign(2 * start, 0);
    r.assign(2 * start, 0);
    for (int i = 0; i < start; i++) {
      l[start + i] = r[start + i] = i;
    }
    build();
  }
  T query (int lf, int rt) {
    ql = lf; qr = rt;
    return query(1);
  }
  void update (int lf, int rt, U val) {
    ql = lf; qr = rt; qv = val;
    update(1);
  }
};
