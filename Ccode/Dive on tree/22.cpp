#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5 * 1e5 + 100;
const int mod = 1004535809;
const int mod1 = 1e9 + 7;
const int INF = 0x3f3f3f3f;
map<pair<int, int>, int> mp;
struct Edge{
    int to, next;
    pair<int, int>w;
}edge[maxn << 1];
 
int tot,head[maxn];
bool vis[maxn];
int sim[maxn],mxson[maxn];
int MX,root,summar;
pair<int, int>dis[maxn];
 
ll Ans;
int S;
 
void init(int n)
{
    tot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1, vis[i] = 0;
    }
}
 
int quickpow(int a, int b, int mod)
{
    int ans = 1;
    while(b > 0)
    {
        if(b & 1) ans = (ll)ans * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return ans;
}
 
inline void addedge(int u, int v, ll fir, ll sec)
{   
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].w.first = fir;
    edge[tot].w.second = sec;
    head[u] = tot++;
}
 
void getroot(int u, int fa)
{
    sim[u] = 1; mxson[u] = 0;
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == fa || vis[v]) continue;
        getroot(v, u);
        sim[u] = sim[u] + sim[v];
        mxson[u] = max(sim[v], mxson[u]);
    }
    mxson[u] = max(mxson[u], S - sim[u]);
    if(mxson[u] < MX){root = u; MX = mxson[u];}
}
 
void getdis(int u, int fa)
{
    ++summar;
    ++mp[dis[u]];
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(vis[v] || v == fa) continue;
        dis[v].first = dis[u].first ^ edge[i].w.first;
        dis[v].second = dis[u].second ^ edge[i].w.second;
        getdis(v, u);
    }
}
 
ll solve(int u, int fir, int sec)
{
    summar = 0;
    mp.clear();
    dis[u].first = fir;
    dis[u].second = sec;
    getdis(u, 0);
    ll tt = (ll)summar * (summar - 1) / 2;
    for(auto it: mp)
    {
        if(it.second >= 2)
        {
            tt -= (ll)it.second * (it.second - 1) / 2;
        }
    }
    return tt;
}
 
void Divide(int u)
{
    Ans += solve(u, 0, 0);
    vis[u] = 1;
    for(int i = head[u];  ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(vis[v]) continue;
        Ans -= solve(v, edge[i].w.first, edge[i].w.second);
        S = sim[v]; 
        root = 0;
        MX = INF;
        getroot(v, 0);
        Divide(root);
    }
    return ;
}
 
int main()
{
    int n;
    scanf("%d",&n);
    init(n);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d",&u,&v,&w);
        int fir = quickpow(2, w, mod);
        int sec = quickpow(2, w, mod1);
        addedge(u, v, fir, sec);
        addedge(v, u, fir, sec);
    }
    Ans = 0;
    MX = INF;
    S = n;
    getroot(1, 0);
    Divide(root);
    printf("%lld\n",Ans);
}