const ll Mod = 1000000007;
/* --- */
using MT = decay<decltype(Mod)>::type;

MT inverse (MT a, MT n) {
  MT u = 0, v = 1;
  while (a != 0) {
    MT q = n / a;
    swap(u, v); v -= q * u;
    swap(n, a); a -= q * n;
  }
  assert(n == 1);
  return u;
}

class mint {
private: MT x;
public:
  void normalize() {
    if (x >= Mod || x < 0) x = (x % Mod) + Mod;
    if (x >= Mod) x -= Mod;
  }
  mint(): x(0) {}
  mint(MT z): x(z) { normalize(); }
  const MT& operator() () const { return x; }

  mint operator+ (const mint& z) { MT r = x + z(); if (r >= Mod) r -= Mod; return mint(r); }
  mint operator- (const mint& z) { MT r = x - z(); if (r < 0) r += Mod; return mint(r); }
  mint operator* (const mint& z) { MT r = x * z(); if (r >= Mod) r %= Mod; return mint(r); }
  mint operator/ (const mint& z) { return (*this) * mint(inverse(z(), Mod)); }

  mint operator+= (const mint& z) { (*this) = (*this) + z; return (*this); }
  mint operator-= (const mint& z) { (*this) = (*this) - z; return (*this); }
  mint operator*= (const mint& z) { (*this) = (*this) * z; return (*this); }
  mint operator/= (const mint& z) { (*this) = (*this) / z; return (*this); }

  friend std::istream& operator>> (std::istream&, mint&);
};

std::istream& operator>> (std::istream& stream, mint& p) {
  MT v; stream >> v; p.x = v; p.normalize(); return stream;
}
std::ostream& operator<< (std::ostream& stream, const mint& p) { return stream << p(); }
mint operator+ (const MT& p, const mint& q) { return mint(p) + q; }
mint operator- (const MT& p, const mint& q) { return mint(p) - q; }
mint operator* (const MT& p, const mint& q) { return mint(p) * q; }
mint operator/ (const MT& p, const mint& q) { return mint(p) / q; }
string to_string (const mint& p) { return to_string(p()); }

mint powMod (mint a, MT b) {
  mint res = 1, x = a;
  while (b > 0) {
    if (b & 1) res *= x;
    x *= x;
    b >>= 1;
  }
  return res;
}
/* --- */
