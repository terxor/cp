/*
template <typename T, typename U, T (*Combine) (T, T), void (*NewUpdate) (U&, U), void (*ApplyUpdate) (T&, U, int) >

Here,
T: Element type
U: Update type
Combine(T, T): Function to combine two elements to produce new element
NewUpdate(U&, U): Function to apply update 'u' if current update is 'v'
- for example, in range addition, this will be addition. If setting values in a range
  this will be overwrite
ApplyUpdate(T& t, U u, int n): Function to apply update u on a node having value t and range size n
*/


string combine (string a, string b) {
  return a + b;
}

void new_upd (char& a, char b) {
  a = b;
}

void apply_upd (string& a, char upd, int len) {
  a = string(len, upd);
}

int main() {
  ios_base::sync_with_stdio(0);
  
  SegmentTree<string, char, combine, new_upd, apply_upd> seg(10, "a", '-');
}
