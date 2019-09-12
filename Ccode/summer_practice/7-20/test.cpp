#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50;
const ll INF = 1e15;
ll love[maxn][maxn];
ll ex_g[maxn];
ll ex_b[maxn];
bool vis_g[maxn];
bool vis_b[maxn];
int match[maxn];
ll slack[maxn];
int n;

bool dfs(int girl)
{
    vis_g[girl] = true;
    for (int boy = 0; boy < n; ++boy)
    {
        if(vis_b[boy]) continue;
        ll gap = ex_g[girl] + ex_b[boy] - love[girl][boy];
        if (gap == 0)
        {
            vis_b[boy] = true;
            if (match[boy] == -1 || dfs(match[boy]))
            {
                match[boy] = girl;
                return true;
            }
        }
        else
        {
            slack[boy] = min(slack[boy], gap);
        }
    }
    return false;
}

ll KM()
{
    memset(match, -1, sizeof match);
    memset(ex_b, 0, sizeof ex_b);
    for (int i = 0; i < n; ++i)
    {
        ex_g[i] = love[i][0];
        for (int j = 1; j < n; ++j)
            ex_g[i] = max(ex_g[i], love[i][j]);
    }
    for (int i = 0; i < n; ++i)
    {
        std::fill(slack, slack + n, INF);
        while (1)
        {
            memset(vis_g, false, sizeof vis_g);
            memset(vis_b, false, sizeof vis_b);
            if (dfs(i))
                break;
            ll d = INF;
            for (int j = 0; j < n; ++j)
            {
                if (!vis_b[j]) d = min(d, slack[j]);
            }
            for (int j = 0; j < n; ++j)
            {
                if (vis_g[j])
                    ex_g[j] -= d;
                if (vis_b[j])
                    ex_b[j] += d;
                else
                    slack[j] -= d;
            }
        }
    }
    ll res = 0;
    for (int i = 0; i < n; ++i)
        res += love[match[i]][i];
    return res;
}

int main()
{
    while (~scanf("%d", &n))
    {
        n *= 2;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%lld", &love[i][j]);
        printf("%lld\n", KM() / 2);
    }
    return 0;
}