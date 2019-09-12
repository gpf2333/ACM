const int maxn = 1500 + 100;
const int maxm = 1000050;
#define typed int
#define pdi pair<typed, int>
const typed INF = 0x3f3f3f3f;
struct Dij{
    struct Edge{
        int to, next, w;
    }edge[maxm << 1];
    int n,tot;
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
        priority_queue<pdi, vector<pdi>, greater<pdi> >q; //note min_heap
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