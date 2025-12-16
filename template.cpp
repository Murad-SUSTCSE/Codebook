#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
typedef tree<int ,null_type,less<int >,rb_tree_tag, tree_order_statistics_node_update> o_set;
typedef tree<int ,null_type,less_equal<int>,rb_tree_tag, tree_order_statistics_node_update> o_multiset;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void solve(){ //order_of_key, find_by_order }
int32_t main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int tc = 1; cin >> tc;
    for(int i = 1;i <= tc;i++) { solve(); } return 0;
}