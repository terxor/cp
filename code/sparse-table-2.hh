template<typename T> class SparseTable {
  T** v;
  int n, k;
  T func (T a, T b) {
    return a + b;
  }

  public:
  SparseTable (vector<T>& a) {
    n = (int)a.size();
    k = 0;
    while ((1 << k) <= n) k++;
    v = (T**)calloc(k, sizeof(T*));
    for (int i = 0; i < k; i++) v[i] = (T*)calloc(n, sizeof(T));

    for (int i = 0; i < n; i++) v[0][i] = a[i];
    for (int j = 1; j < k; j++) 
      for (int i = 0; i < n - (1 << j) + 1; i++) 
        v[j][i] = func(v[j - 1][i], v[j - 1][i + (1 << (j - 1))]);
  }

  T query (int i, int j) {
    int p = 8 * (int)sizeof(int) - __builtin_clz(j - i + 1) - 1;
    if ((1 << p) == (j - i + 1)) return v[p][i];
    return func(v[p][i], query(i + (1 << p), j));
  }

  ~SparseTable() {
    for (int i = 0; i < k; i++) free(v[i]);
    free(v); 
  }
};

