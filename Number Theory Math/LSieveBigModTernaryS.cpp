int a[], n elements;

int mx  = 0;
int ans = 0;
for (int i = 0; i < n; i++) {
   mx  = max(mx+a[i], (int)0);
   ans = max(ans, mx);
}
//
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
//

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
//
int mod = 1e9 + 7;

int bigmod(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
      if (b & 1)
         res = res * a % m;
      a = a * a % m;
      b >>= 1;
   }
    return res;
}
int inversemod(int n) {
   return binpow(n, mod-2, mod)%mod;
}

// linear sieve.
std::vector <int> prime;
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


//
// #include <ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// using namespace __gnu_cxx;
// template <typename T> using oset = 
// tree<T, null_type, less<T>, 
// rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


