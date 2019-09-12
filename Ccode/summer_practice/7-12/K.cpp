#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const ll INF = 1e15;
 
struct Node {
    int v;
    long long c;
    int flag;
    Node (int _v = 0, ll _c = 0, int _flag = 0) : v(_v), c(_c), flag(_flag) {}
    bool operator < (const Node &rhs) const {
        return c > rhs.c;
    }
};
 
struct Edge {
    int v;
    int cost;
    Edge (int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};

vector<Edge>E[maxn];
bool vis[maxn][2];
ll dist[maxn][2];
 
void Dijkstra(int n, int s) {
    for (int i = 0; i <= n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
        vis[i][0] = vis[i][1] = 0;
    }
    priority_queue<Node>que;
    dist[s][0] = 0;
    que.push(Node(s, 0, 0));
    while (!que.empty()) {
        Node tep = que.top(); que.pop();
        int u = tep.v;
        int flag = tep.flag;
        if (vis[u][flag]) continue;
        vis[u][flag] = 1;
        for (int i = 0; i < (int)E[u].size(); i++) {
            int v = E[u][i].v;
            long long cost = E[u][i].cost;
            if (!vis[v][0] && dist[v][0] > dist[u][flag] + cost) {
                dist[v][1] = dist[v][0];
                dist[v][0] = dist[u][flag] + cost;
                que.push(Node(v, dist[v][0], 0));
                que.push(Node(v, dist[v][1], 1));
            } else if (!vis[v][1] && dist[v][1] > dist[u][flag] + cost) {
                dist[v][1] = dist[u][flag] + cost;
                que.push(Node(v, dist[v][1], 1));
            }
        }
    }
}
 
inline void addedge(int u, int v, int w) {
    E[u].push_back(Edge(v, w));
}
 
int main() {
    int T,n, m, u, v, w;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&m);
        for (int i = 0; i <= n; i++) E[i].clear();
        for(int i = 0; i < m; ++i){
            scanf("%d%d%d",&u, &v,&w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        if(m == 1){
            printf("%lld\n", (long long)3 * (long long)w);
            continue ;
        }
        Dijkstra(n, 1);
        printf("%lld\n", dist[n][1]);
    }
    return 0;
}