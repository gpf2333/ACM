#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
struct Edge{
    int u, v, w;
}edge[maxn];
bool cmp1(const Edge &a, const Edge &b){
    return a.w < b.w;
}
struct Query{
    int id, w;
}query[maxn];
bool cmp2(const Query &a, const Query &b){
    return a.w < b.w;
}
int fa[maxn], rk[maxn], siz[maxn];
ll b[maxn];
ll ans[maxn];
void init(){
    for(int i = 0; i < maxn; ++i){
        fa[i] = i;
        rk[i] = 0;
        siz[i] = 1;
    }
}
int Find(int x){
    if(x == fa[x]) return x;
    int rt = Find(fa[x]);
    return (fa[x] = rt);
}
inline ll C(int n){
    return (ll)n * (n - 1) / 2;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i < n; ++i){
        cin >>edge[i].u >> edge[i].v >> edge[i].w;
    }
    for(int i = 1; i <= m; ++i){
        cin >>  query[i].w;
        query[i].id = i;
    }
    sort(edge + 1, edge + n, cmp1);
    sort(query + 1, query + 1 + m, cmp2);
    init();
    ll sum = 0;
    for(int i = 1, j = 1; i <= m; ++i){
        for(; j < n && edge[j].w <= query[i].w; ++j){
            int u = edge[j].u, v = edge[j].v;
            u = Find(u), v = Find(v);
            if(u == v) continue ;
            if(rk[u] > rk[v]){
                fa[v] = u;
                sum -= C(siz[v]);
                sum -= C(siz[u]);
                siz[u] += siz[v];
                sum += C(siz[u]);
            }else{
                fa[u] = v;
                sum -= C(siz[u]);
                sum -= C(siz[v]);
                siz[v] += siz[u];
                sum += C(siz[v]);
                if(rk[u] == rk[v]) ++rk[v]; 
            }
        }
        ans[query[i].id] = sum;
    }
    for(int i = 1; i <= m; ++i){
        cout << ans[i] << " ";
    }
    return 0;
}