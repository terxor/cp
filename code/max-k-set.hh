/* T = int or long long */
template <typename T>
class SumMultiset {
	private:
	T cnt, sm;
	map<T, T> freq;

	public:
	SumMultiset (): cnt(0), sm(0) {}

	void add (T x, T k) {
		assert(k > 0);
		sm += x * k;	
		freq[x] += k;
		cnt += k;
	}

	void remove (T x, T k) {
		assert(k > 0);	
		auto itr = freq.find(x);
		assert(itr != freq.end() && itr->second >= k);
		itr->second -= k;
		sm -= k * x;
		cnt -= k;
		if (itr->second == 0) freq.erase(itr);
	}

	T minElement () {
		assert(cnt > 0);
		return freq.begin()->first;
	}

	T maxElement () {
		assert(cnt > 0);
		return (--freq.end())->first;
	}
	
	bool empty () { return cnt == 0; }
	T size() { return cnt; }
	T frequency (T x) {
		auto itr = freq.find(x);
		if (itr == freq.end()) return 0;
		return itr->second;
	}
	T sum () { return sm; }
};

struct MaxKSet {
	SumMultiset<ll> S, R;
	MaxKSet(ll _k): k(_k) { n = 0; }
	ll n, k;
	void add (ll x) {
		if (n < k) S.add(x, 1); 
		else {
			ll z = S.minElement();	
			if (x > z) { S.remove(z, 1); S.add(x, 1); R.add(z, 1); }		
			else R.add(x, 1);
		}
		n++;
	}

	void remove (ll x) {
		if (S.frequency(x) > 0) {
			S.remove(x, 1);
			if (!R.empty()) {
				ll z = R.maxElement();
				S.add(z, 1);
				R.remove(z, 1);
			}
		}
		else {
			assert(R.frequency(x) > 0);
			R.remove(x, 1);
		}
		n--;
	}

	ll sum () { return S.sum(); }
	ll remSum() { return R.sum(); }

};
