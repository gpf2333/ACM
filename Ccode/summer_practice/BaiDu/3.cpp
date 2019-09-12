#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 1e3 + 10;
const int maxm = 2e3 + 10;
#define typed long long
#define pdi pair<typed, int>
const typed INF = 1e18;
struct Dij{
    struct Edge{
        int to, next, w;
    }edge[maxm << 1];
    int n, m, tot;
    int head[maxn];
    bool vis[maxn];
    void init(int N){
        tot = 0;
        this->n = N;
        for(int i = 0; i <= n; ++i) head[i] = -1;
    }
    void addedge(int u, int v, int w){
        edge[tot] = (Edge){v, head[u], w};
        head[u] = tot++;
    }
    typed d[maxn];
    int pre[maxn];
    inline void dijkstra(int s){
        for(int i = 0; i <= n; ++i){
            d[i] = INF, vis[i] = 0;
            pre[i] = 0;
        }
        priority_queue<pdi, vector<pdi>, greater<pdi> >q;
        d[s] = 0;
        q.emplace(0, s);
        while(!q.empty()){
            int u = q.top().second; q.pop(); 
            if(vis[u]) continue ;
            vis[u] = 1;
            for(int i = head[u]; ~i; i = edge[i].next){
                int v = edge[i].to;
                if(d[v] > d[u] + edge[i].w){
                    d[v] = d[u] + edge[i].w;
                    q.emplace(d[v], v);
                    if(u != s) pre[v] = max(pre[u], u); // u != s 端点不能算，三点以上才计算
                    else pre[v] = pre[u];
                }else if(d[v] == d[u] + edge[i].w){ //多条最短路
                    int tmp;
                    if(u != s) tmp = max(pre[u], u);
                    else tmp = pre[u];
                    if(tmp < pre[v]){
                        pre[v] = tmp;
                        q.emplace(d[v], v);
                    }
                }
            }
        }
        return ;
    }

    int solve(int n){
        int res = 0;
        for(int i = 1; i <= n; ++i){
            dijkstra(i);
            for(int j = 1; j <= n; ++j){
                res = (res + (long long)pre[j]) % mod;
            }
        }
        return res;
    }

}D;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, m;
        scanf("%d%d", &n, &m);
        D.init(n);
        for(int i = 1; i <= m; ++i){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            D.addedge(u, v, w);
            D.addedge(v, u, w);
        }
        printf("%d\n", D.solve(n));
    }
    return 0;
}