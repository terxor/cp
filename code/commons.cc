// Divisors in O(sqrt(x))
template<typename T> vector<T> divisors (T x) {
  vector<T> u, v;
  for (T i = 1; i * i <= x; i++) {
    if (x % i != 0) continue;
    u.push_back(i);
    T t = x / i;
    if (t != i) v.push_back(t);
  }
  u.insert(u.end(), v.rbegin(), v.rend());
  return u;
}

vector<int> primes (int max) {
  vector<bool> is_prime(max + 1, 1);
  vector<int> res;
  for (int i = 2; i <= max; i++) if (is_prime[i]) {
    res.push_back(i);
    for (int j = i + i; j <= max; j += i) is_prime[j] = 0;
  }
  return res;
}

/** modular **/

// inverse
template<typename T> T inverse (T a, T n) {
  T u = 0, v = 1, z = n;
  while (a != 0) {
    T q = n / a;
    swap(u, v); v -= q * u;
    swap(n, a); a -= q * n;
  }
  assert(n == 1);
  return (u + z) % z;
}
