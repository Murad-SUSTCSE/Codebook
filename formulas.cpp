/* ---------- POLYGON ----------
Area of polygon (shoelace):
Area = 0.5 * |sum(x[i]*y[i+1] - x[i+1]*y[i])|
Centroid of polygon:
Cx = sum((xi + xi+1) * cross(i,i+1)) / (6*Area)
Cy = sum((yi + yi+1) * cross(i,i+1)) / (6*Area)
Point inside polygon (ray casting):
Count intersections of ray to +x
Odd = inside, Even = outside
Convex polygon point inside:
For all edges (Pi, Pi+1):
cross(Pi+1-Pi, X-Pi) >= 0 (or <=0 consistently)
*/
/* ---------- TRIANGLE ----------
Area using cross:
Area = |cross(B-A, C-A)| / 2
Circumcenter:
Intersection of perpendicular bisectors
(Omitted formula – compute via lines)
Incenter:
I = (a*A + b*B + c*C) / (a+b+c)
where:
Centroid:
G = (A+B+C)/3
Orthocenter:
H = A + B + C - 2*O (O = circumcenter)
Radius:
Inradius r = Area / s
Circumradius R = (a*b*c) / (4*Area)
Angle between vectors:
cos(theta) = dot(u,v)/(|u||v|)
*/
/* ---------- COMBINATORICS & MATH ----------
Stirling Numbers of the Second Kind S(n,k) Parity:
Odd  = (((n - k) & ((k - 1) / 2)) == 0)
Even = otherwise

Sum of Powers (Faulhaber's Formula):
// Based on image_362f5e.png
sum(k^p) for k=1..n = (1 / (p + 1)) * sum_{r=0 to p} [ C(p+1, r) * B_r * n^(p+1-r) ]
* Note: B_r represents the r-th Bernoulli number (using B_1^+ = +1/2).

Bracket Arrangements:
// DP[i][j]: ways to arrange i pairs of brackets into j valid non-empty blocks
DP[i][j] = (j * C(2i - j, i - j) * inv(2i - j)) % M
*/

