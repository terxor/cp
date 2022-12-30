/* Linear Time Sieve supporting fast factorization */

template <int MX>
struct LinearSieve {
	int lp[MX + 10];
	int jmp[MX + 10]; /* Avoids division but uses double space */
	vector<int> pr;
	LinearSieve () {
		memset(lp, 0, sizeof lp);
		for (int i = 2; i <= MX; i++) {
			if (!lp[i]) { lp[i] = i; pr.push_back(i); }
			for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= MX; j++)
				lp[pr[j] * i] = pr[j];
		}
		/* Comment the line below if not using jmp array */
		for (int i = 2; i <= MX; i++) jmp[i] = i / lp[i];
	}

	bool isPrime (int x) { return (lp[x] == x); }
	vector<int> factorize (int x) {
		assert(x <= MX);
		vector<int> res;
		while (lp[x] != 0) {
			res.push_back(lp[x]);
			// x /= lp[x]; 
			/* Uncomment the line above and comment the line below if not using jmp array */
			x = jmp[x];
		}
		return res;
	}
};

LinearSieve<10000000> sieve;

int main() {
	int x;
	while (scanf("%d", &x) != -1)
		dbg(sieve.factorize(x));
}