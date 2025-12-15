#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define f(i, n) for(int i = 0; i < (n); i++)
#define sd(i) scanf("%d", &i)
#define tcase int t; sd(t); for(int casee = 1; casee <= t; casee++)
#define en printf("\n")
#define mod 1000000007
using namespace std;
vector<vector<ll>> matmultiply(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    if(a[0].size() != b.size()) return vector<vector<ll>>(0);
    else {
        vector<vector<ll>> ans(a.size(), vector<ll>(b[0].size(),0));
        f(i,a.size()) {
            f(j,b[0].size()) {
             f(k,b.size()) ans[i][j] = (ans[i][j] + ((a[i][k]*b[k][j])%mod))%mod;
            }
        }
        return ans;
    } 
}
vector<vector<ll>> matexpo(vector<vector<ll>>& a, ll exp) {
    vector<vector<ll>> res(a[0].size(), vector<ll>(a[0].size(),0));
    f(i,a[0].size()) res[i][i] = 1;
    while(exp > 0) {
        if(exp&1)  res = matmultiply(res,a);
        a = matmultiply(a,a);
        exp /= 2;
    }
    return res;
}
int main() {
    ll n;
    scanf("%lld", &n);
    if(n==0) printf("0\n");
    else {
         vector<vector<ll>> arr(2,vector<ll>(2,1));
         arr[1][1] = 0;
         arr = matexpo(arr,n);
         printf("%lld\n",arr[0][1]);
    }

    return 0;
}