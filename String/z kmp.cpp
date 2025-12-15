#include<bits/stdc++.h>
 
using namespace std;
 
#define IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define   endl              "\n"
#define   size(a)           (int)a.size()
 
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> z_function(string pattern, string text) {
   string s = pattern + "$" + text;
   int n = size(s);
   vector<int> z(n);
   for (int i = 1, l = 0, r = 0; i < n; ++i) {
      if (i <= r)
         z[i] = min (r - i + 1, z[i - l]);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]])
         ++z[i];
      if (i + z[i] - 1 > r)
         l = i, r = i + z[i] - 1;
   }
   return z;
}
void solve() {
   string text, pattern;
   cin >> text >> pattern;
   vector<int> z = z_function(pattern, text);
   int ans = 0;
   for (int i : z) {
      ans += (i == size(pattern));
   }
   cout << ans << endl;
}
int32_t main() {
   IO;
   int TestCase = 1;
   // cin >> TestCase;
   while(TestCase--)
      solve();
   
   return 0;
}
