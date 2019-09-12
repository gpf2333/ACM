#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 100;
const int maxm = 1e5;
const ll INF = 1e15;
struct Dij{
    struct Edge{
        int to,next;
        int w;
    }edge[maxm];
    int n,sum,tot;
    int head[maxn];
    bool vis[maxn];
    void init(int N){
        tot = 0;
        this->n = N;
        for(int i = 0; i <= N; ++i) head[i] = -1;
    }
    struct node{
        int id;
        long long dis;
        node(){};
        node(int iid, long long dd):id(iid),dis(dd){};
        bool operator < (const node &d) const{
            return dis > d.dis;
        }
    }d[maxn];
    inline void addedge(int u,int v,int w){
        edge[tot] = (Edge){v,head[u],w}, head[u] = tot++;
    }
    void dijkstra(int s,int t){
        for(int i = 0; i <= n; ++i){
            d[i].dis = INF, d[i].id = i, vis[i] = 0;
        }
        priority_queue<node>q;
        d[s].dis = 0;
        q.push(d[s]);
        while(!q.empty()){
            int u = q.top().id; q.pop();
            if(vis[u]) continue ;
            vis[u] = 1;
            for(int i = head[u]; ~i; i = edge[i].next){
                int v = edge[i].to;
                //if(vis[v]) continue ;
                if(d[v].dis > d[u].dis + edge[i].w){
                    d[v].dis = d[u].dis + edge[i].w;
                    q.push(d[v]);
                }
            }
        }
        return ;
    }
}D;

#define captype long long
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
    captype max_flow(int s,int t,int n){
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

int a[maxn],b[maxn],c[maxn];
bool vis[maxn];
int main(){
    int n, m, T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n, &m);
        D.init(n);
        int sum = 0;
        while(m--){
            scanf("%d%d%d",&a[sum],&b[sum],&c[sum]);
            D.addedge(a[sum],b[sum],c[sum]);
            //D.addedge(b[sum],a[sum],c[sum]);
            ++sum;
        }
        D.dijkstra(1,n);
        if(n == 1 && D.d[n].dis == INF){
            puts("0");
            continue ;
        }
        F.init(n);
        int u, v;
        int s = 0, t = n + 1;
        F.addedge(s, 1, INF);
        F.addedge(n, t, INF);
        for(int i = 0; i <= n; ++i) vis[i] = 0;
        for(int i = 0; i < sum; ++i){
            u = a[i], v = b[i];
            if(D.d[u].dis > D.d[v].dis) swap(u,v);
            if(D.d[v].dis - D.d[u].dis == c[i]){
                F.addedge(u, v, c[i]);
                vis[u] = vis[v] = 1;
            } 
        }
        int cnt = 2;
        for(int i = 1; i <= n; ++i) if(vis[i]) ++cnt;
        printf("%lld\n",F.max_flow(s, t, cnt));
    }
    return 0;
}
