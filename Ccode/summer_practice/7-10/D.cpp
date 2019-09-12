#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int maxn = 105;
const int cnt[][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {2, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 1},
    {3, 0, 0, 0},
    {0, 2, 0, 0}};
const int p[] = {2, 3, 5, 7};
const int mod = 1e9 + 7;
 
int dp[105][66666];
vector<int> l, r;
int sz = 0;
 
void init(vector<int>& x)
{
    static char buf[maxn];
    scanf("%s", buf);
    int n = strlen(buf);
    x.resize(n);
    for (int i = 0, j = n - 1; ~j; i++, j--) x[i] = buf[j] - '0';
}
void init()
{
    init(l), init(r);
    assert(l.size() <= r.size());
    l.resize(r.size());
}
 
int num[60][38][26][22];
 
int dfs(int pos, int a, int b, int c, int d, bool lead = true, bool limit_l = true, bool limit_r = true)
{
    if (!~pos) return !(a || b || c || d);
    if (a < 0 || b < 0 || c < 0 || d < 0) return 0;
    int h = num[a][b][c][d];
    assert(~h);
    if (!limit_l && !limit_r && !lead && ~dp[pos][h]) return dp[pos][h];
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
        if (limit_l && i < l[pos]) continue;
        if (limit_r && i > r[pos]) continue;
        if (!lead && !i) continue;
        ans += dfs(pos - 1,
                   a - cnt[i][0],
                   b - cnt[i][1],
                   c - cnt[i][2],
                   d - cnt[i][3],
                   lead && i == 0,
                   limit_l && i == l[pos],
                   limit_r && i == r[pos]);
        if (ans >= mod) ans -= mod;
    }
    if (!limit_l && !limit_r && !lead) dp[pos][h] = ans;
    return ans;
}
int solve()
{
    ll k;
    scanf("%lld", &k);
    int cnt[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        if (k % p[i] == 0)
        {
            do
            {
                k /= p[i];
                cnt[i]++;
            } while (k % p[i] == 0);
        }
    }
    if (k > 1) return 0;
    return dfs(r.size() - 1, cnt[0], cnt[1], cnt[2], cnt[3]);
}
 
int main()
{
    memset(num, -1, sizeof(num));
    memset(dp, -1, sizeof(dp));
    const double lg2 = log10(2.0), lg3 = log10(3.0), lg5 = log10(5.0), lg7 = log10(7.0);
    for (int i = 0; i < 60; i++)
        for (int j = 0; j < 38; j++)
            for (int k = 0; k < 26; k++)
                for (int l = 0; l < 22; l++)
                {
                    if (((lg2 * i) + (lg3 * j) + (lg5 * k) + (lg7 * l)) > 18.0001) break;
                    num[i][j][k][l] = sz++;
                }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        init();
        printf("%d\n", solve());
    }
}