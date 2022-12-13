using namespace std;
#define dbg(...) cerr << "[" << __func__ << ":" << __LINE__ << "] " << #__VA_ARGS__ << " =" << dbg_str(__VA_ARGS__)

template<typename U> string dbg_container (U);
template<typename U, typename V> string to_string (pair<U, V>);

string to_string (const char* e) {
  return "\"" + string(e) + "\"";
}

string to_string (const string& e){
  return "\"" + e + "\"";
}

string to_string (char e) {
  return "\'" + string(1, e) + "\'";
}

string to_string (bool e) {
  return e ? "true" : "false";
}

template<typename U> string to_string (vector<U> e) {
  return dbg_container(e);
}

template<typename U> string to_string (set<U> e) {
  return dbg_container(e);
}

template<typename U> string to_string (queue<U> e) {
  return dbg_container(e);
}

template<typename U, typename V> string to_string (map<U, V> e) {
  return dbg_container(e);
}

template<typename U, typename V> string to_string (pair<U, V> e){
  return "(" + to_string(e.first) + ", " + to_string(e.second) + ")";
}

template<typename U> string dbg_container (U e) {
  string s = "[";
  int f = 1;
  for (auto& x : e) {
    if (!f) s += ", ";
    s += to_string(x);
    f = 0;
  }
  return s + "]";
}

string dbg_str () {
  return " \n";
}

template <typename U, typename... V> string dbg_str (U u, V... v) {
  return " " + to_string(u) + dbg_str(v...);
}

