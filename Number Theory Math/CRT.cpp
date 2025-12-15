__int128 ExU(__int128 a, __int128 b, __int128 &x, __int128 &y) {
   if(b == 0) {
      x = 1;
      y = 0;
      return a;
   }
   __int128 x1, y1;
   __int128 d = ExU(b, a%b, x1, y1);
   x = y1;
   y = x1 - (a/b)*y1;
   return d;
}
void solve() {
   cout << "Case " << ii++ << ": ";
   int n; cin >> n;
   vector<int> a(n), m(n);
   for (int i = 0; i < n; i++) cin >> m[i] >> a[i];
   int a1 = a[0], m1 = m[0];
   for (int i = 1; i < n; i++) {
      __int128 a2 = a[i], m2 = m[i];
      __int128 x, y;
      __int128 g = ExU(m1, m2, x, y);
      if((a1-a2) % g != 0) {
         cout << "Impossible" << endl;
         return;
      }
      __int128 k = (a1-a2) / g, lcm = (m1/g) * m2;
      __int128 a = a1 - m1*(k * x);
      a1 = (a % lcm);
      if(a1 < 0) a1 += lcm;
      m1 = lcm;
   }
   cout << a1 << endl;
}