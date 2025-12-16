int a[], n elements;
int mx  = 0; int ans = 0;
for (int i = 0; i < n; i++) {
   mx  = max(mx+a[i], (int)0);
   ans = max(ans, mx);
}
#define sz 1000
vector <int> prime;
bitset <sz> bs;
void sieve() {
   bs.set(); // all bit = 1..
   bs[0] = bs[1] = 0;
   prime.push_back(2);
   for (int i = 3; i <= sz; i += 2) {
      if(bs[i]) {
         for (int j = i*i; j <= sz; j += i)
            bs[j] = 0;
         prime.push_back(i);
      }
   }
}
void solve()
{
   int n = 12;
   int a[] = {60, 70, 80, 90, 100, 200, 400, 500, 600, 700, 900, 1000};
   int r = n-1; int l = 0;
   // cout << (r-l) / 2;
   while(l < r) {
      int c = (r-l) / 3;
      int m1 = l + c;
      int m2 = r - c;
      // cout << a[m1] << ' ' << a[m2] << endl;
      if(a[m1] < a[m2]) {
         r = m2 - 1;
      } else if(a[m1] > a[m2]) {
         l = m1 + 1;
      } else {
         l = m1 + 1; r = m2 - 1;
      }
   }  
   cout << a[l] << endl;
}
int mod = 1e9 + 7;
// linear sieve.
vector <int> prime;
bool is_composite[MAXN];
void sieve (int n) {
	std::fill (is_composite, is_composite + n, false);
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

