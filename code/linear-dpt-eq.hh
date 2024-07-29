int gcd_ext (int a, int b, int& x, int& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  
  int x1, y1, g;
  g = gcd_ext(b % a, a, x1, y1);
  // (b - (b/a)*a)x1 + ay1 = g
  x = y1 - (b / a) * x1;
  y = x1;
  return g;
}

int main() {
  
  int a, b, c;
  cin >> a >> b >> c;
  
  int x, y;
  int g = gcd_ext(a, b, x, y);

  if (c % g != 0) {
    cout << "No solution exists\n";
    return;
  }
  
  x *= (c / g);
  y *= (c / g);
  assert(a * x + b * y == c);
  cout << a << "*" << x << " + " << b << "*" << y << " = " << c << '\n';
}
