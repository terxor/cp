/* Chinese remainder theorem for small integers
   Product of divisors in int range */
Long inverse (Long a, Long n) {
  Long u = 0, v = 1, t = n;
  while (a != 0) {
    Long q = n / a;
    swap(u, v); v -= q * u;
    swap(n, a); a -= q * n;
  }
  assert(n == 1);
  return (u + t) % t;
}
 
Long crt (vector<Long> div, vector<Long> rem) {
  assert(rem.size() == div.size());
  Long k = div.size(), pr = 1;
  for (auto d : div) pr *= d;
  vector<Long> y(k), z(k);
  for (int i = 0; i < k; i++) y[i] = pr / div[i];
  for (int i = 0; i < k; i++) z[i] = inverse(y[i], div[i]);
  Long ans = 0;
  for (int i = 0; i < k; i++) {
    Long u = rem[i];
    (u *= y[i]) %= pr;
    (u *= z[i]) %= pr;
    (ans += u) %= pr;
  }
  return ans;
}