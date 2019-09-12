#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
mt19937_64 rnd;

const int maxn = 5e5 + 100;
unordered_map<int,ull>ump;
vector<pair<int,ull> >G[maxn];
map<ull,int>ans;
int n;
ull get_hash(int x)
{
    if(ump.count(x)) return ump[x];
    else return ump[x] = rnd();
}

void dfs(int u,int fa,ull w)
{
    ans[w]++;
    for(auto &it:G[u])
    {
        int v = it.first;
        if(v == fa) continue;
        dfs(v,u,w ^ it.second);
    }
}

int main()
{
    scanf("%d",&n);
    int u,v;ull w;
    for(int i = 1;i < n; ++i)
    {
        scanf("%d%d%u",&u,&v,&w);
        G[u].push_back(make_pair(v,get_hash(w)));
        G[v].push_back(make_pair(u,get_hash(w)));
    }
    dfs(1,0,0);
    ll cnt = 1LL * n * (n - 1) / 2;
    for(auto it:ans) cnt -= 1LL * it.second * (it.second - 1LL) / 2 ;
    printf("%lld\n",cnt);
    return 0;
}