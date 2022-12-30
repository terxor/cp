/* Tested:
	https://www.spoj.com/problems/TDPRIMES/
		primes upto 10^8 in time < 0.7s and memory < 50MB
*/

template <int MX> struct Sieve {
	bitset<MX + 10> isPrime;
	vector<int> pr;
	Sieve () {
		isPrime.set(); isPrime[0] = isPrime[1] = false;
		for (int i = 4; i <= MX; i += 2) isPrime[i] = false;
		for (int i = 3; i * i <= MX; i += 2) if (isPrime[i])
			for (int j = i * i; j <= MX; j += (i << 1)) isPrime[j] = false;
		for (int i = 0; i <= MX; i++) if (isPrime[i]) pr.push_back(i);
	}
};

Sieve<(int)1e8> sieve;

int main() {
	vector<int>& pr = sieve.pr;
	for (int i = 0; i < (int)pr.size(); i += 100)
		printf("%d\n", pr[i]);
}

