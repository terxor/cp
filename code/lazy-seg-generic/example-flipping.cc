/* Operations:
- Find number of set bits in a range
- Flip bits in a range

We will use T as int: number of set bits
We will use U as int: whether to flip
*/

/* combine number of set bits */
int combine (int a, int b) {
  return a + b;
}

/* add new update - only parity of number of flips matter */
void new_upd (int& a, int b) {
  a = ((a + b) & 1)
}

/* apply update on range: if 'a' bits then flip means we get (len - a) bits */
void apply_upd (int& a, int upd, int len) {
  a = (upd ? len - a : a);
}

int main() {
  ios_base::sync_with_stdio(0);
  
  SegmentTree<int, int, combine, new_upd, apply_upd> seg(10, 0, 0);
}
