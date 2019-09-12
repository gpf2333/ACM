#include<bits/stdc++.h>
using namespace std;
const int maxn = 1500 + 100;
const int maxm = 1000050;
#define typed int
#define pdi pair<typed, int>
const typed INF = 0x3f3f3f3f;
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
    inline void dijkstra(int s){
        for(int i = 0; i <= n; ++i){
            d[i] = INF, vis[i] = 0;
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
                }
            }
        }
        return ;
    }

}D;

#define captype int
struct SAP{
    struct Edge{
        int from,to,next;
        captype cap;
    }edge[maxm];
    int tot,head[maxn];
    int dis[maxn],cur[maxn],pre[maxn],gap[maxn];
    void init(int n){
        tot = 0;
        for(int i = 0; i <= n; ++i) head[i] = -1;
    }
    inline void addedge(int u,int v,captype c,captype rc = 0){
        edge[tot] = (Edge){u,v,head[u],c}, head[u] = tot++;
        edge[tot] = (Edge){v,u,head[v],rc}, head[v] = tot++;
    }
    captype max_flow(int s,int t,int n){ //包括源点和汇点在内的总点数
        for(int i = 0; i < maxn; ++i){
            gap[i] = dis[i] = 0;
            cur[i] = head[i];
        }
        pre[s] = -1, gap[s] = n;
        captype ans = 0;
        int u = s;
        while(dis[s] < n){
            if(u == t){
                captype minn = INF;
                int v;
                for(int i = pre[u]; ~i; i = pre[edge[i^1].to]){
                    if(minn > edge[i].cap){
                        minn = edge[i].cap, v = i;
                    }
                }
                for(int i = pre[u]; ~i; i = pre[edge[i^1].to]){
                    edge[i].cap -= minn;
                    edge[i^1].cap += minn;
                }
                ans += minn;
                u = edge[v^1].to;
                continue ;
            }
            bool ok = 0;
            int v;
            for(int i = cur[u]; ~i; i = edge[i].next){
                v = edge[i].to;
                if(edge[i].cap > 0 && dis[u] == dis[v] + 1){
                    ok = 1, cur[u] = pre[v] = i;
                    break ;
                }
            }
            if(ok){
                u = v; continue ;
            }
            int mind = n;
            for(int i = head[u]; ~i; i = edge[i].next){
                if(edge[i].cap > 0 && mind > dis[edge[i].to]){
                    mind = dis[edge[i].to];
                    cur[u] = i;
                }
            }
            --gap[dis[u]];
            if(!gap[dis[u]]) return ans;
            dis[u] = mind + 1;
            ++gap[dis[u]];
            if(u != s) u = edge[pre[u]^1].to;
        }
        return ans;
    }
}F;

const int mx = 1000050; 
int a[mx],b[mx],c[mx];
bool vis[1550];
int main(){
    int n,T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        D.init(n);
        int m = 0;
        while(1){
            scanf("%d%d%d",&a[m],&b[m],&c[m]);
            if(a[m] ==0 && b[m] == 0 && c[m] == 0) break ;
            D.addedge(a[m],b[m],c[m]);
            D.addedge(b[m],a[m],c[m]);
            ++m;
        }
        D.dijkstra(1);
        if(n == 1 || D.d[n] == INF){
            puts("0");
            continue ;
        }
        F.init(n);
        int u,v;
        int s = 0, t = n + 1;
        F.addedge(s,1,INF);
        F.addedge(n,t,INF);
        for(int i = 0; i <= n; ++i) vis[i] = 0;
        for(int i = 0; i < m; ++i){
            u = a[i], v = b[i];
            if(D.d[u] > D.d[v]) swap(u,v);
            if(D.d[v] - D.d[u] == c[i]){
                F.addedge(u,v,1);
                vis[u] = vis[v] = 1;
            }
        }
        int cnt = 2;
        for(int i = 1; i <= n; ++i) if(vis[i]) ++cnt;
        printf("%d\n",F.max_flow(s,t,cnt));
    }
    return 0;
}