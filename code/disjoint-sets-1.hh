/* Disjoint sets - Union by size */
/* inline implementation */
vector<int> s(n, 1), p(n);
for (int i = 0; i < n; i++) p[i] = i;
 
function<int(int)> findLeader = [&] (int x) {
  if (p[x] == x) return x;
  return p[x] = findLeader(p[x]);
};
 
auto unionSets = [&] (int u, int v) {
  u = findLeader(u); v = findLeader(v);
  if (u == v) return;
  if (s[u] > s[v]) swap(u, v);
  s[v] += s[u];
  p[u] = v;
};
