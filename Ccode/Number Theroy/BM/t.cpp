#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double ld;
const double eps = 1e-7;
const int maxn = 1e5 + 5;
typedef vector<ld> vld;
vld ps[maxn];
int fail[maxn];
ld x[maxn], delta[maxn];
int n;
int pn; 
ll a[maxn];
void init(int n)
{
    a[1] = 1;
   x[1] = a[1];
    for(int i = 2; i <= n; i++){
        a[i] = 0;
        for(int j = 1; j < i; j++){
            a[i] += a[j] * j;
        }
        // cout << a[i] << endl;
        x[i] = a[i];
        a[i] %= i;
    }
}

int main(void)
{
    while (~scanf("%d", &n) && n) {
        init(n);
        pn = 0;
        // for (int i = 1; i <= n; ++i) scanf("%lf", x + i);
        for (int i = 1; i <= n; ++i) {
            ld dt = -x[i];
            for (int j = 0; j < ps[pn].size(); ++j) dt += x[i - j - 1] * ps[pn][j];
            delta[i] = dt;
            if (fabs(dt) <= eps) continue;
            fail[pn] = i;
            if(!pn) { ps[++pn].resize(1); continue; }
            vld&ls = ps[pn - 1];
            ld k = -dt / delta[fail[pn - 1]];
            vld cur;
            cur.resize(i - fail[pn - 1] - 1);
            cur.push_back(-k);
            for (int j = 0; j < ls.size(); ++j) cur.push_back(ls[j] * k);
            if (cur.size() < ps[pn].size()) cur.resize(ps[pn].size());
            for (int j = 0; j < ps[pn].size(); ++j) cur[j] += ps[pn][j];
            ps[++pn] = cur;
        }
        int len = (int)ps[pn].size();
        for (int i = 0; i < len; ++i)
            printf("%g%c", ps[pn][i], " \n"[i == len - 1]);
    }
    return 0;
}