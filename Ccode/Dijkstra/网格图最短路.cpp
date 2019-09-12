#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
const double eps = 1e-8;
const int maxm = 1005 * 1005;
#define typed double
#define pdi pair<typed, int>
const typed INF = 1e18;
struct Dij{
    struct Edge{
        int to, next;
        double w;
    }edge[maxm << 4];
    int n,tot;
    int head[maxm + 100];
    bool vis[maxm + 100];
    void init(int N){
        tot = 0;
        this->n = N;
        for(int i = 0; i <= n; ++i) head[i] = -1;
    }
    void addedge(int u, int v, double w){
        edge[tot] = (Edge){v, head[u], w};
        head[u] = tot++;
    }
    typed d[maxm + 100];
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

struct Rec{
    int x1, x2, y1, y2;
}a[maxn];
int numx[maxn], numy[maxn];
int num[maxn][maxn];
int sum[maxn][maxn];
int dir[4][2] = {1, 0, 0, -1, -1, 0, 0, 1};
int main(){
    int T, n;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        int cntx = 0, cnty = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
            numx[++cntx] = a[i].x1, numx[++cntx] = a[i].x2;
            numy[++cnty] = a[i].y1, numy[++cnty] = a[i].y2;
        }
        int ax, ay, bx, by;
        scanf("%d%d%d%d", &ax, &ay, &bx, &by);
        if(ax == bx && ay == by){
            printf("%.5f\n", 0.00000); continue ;
        }
        numx[++cntx] = ax, numx[++cntx] = bx;
        numy[++cnty] = ay, numy[++cnty] = by;
        sort(numx + 1, numx + cntx + 1);
        int totx = unique(numx + 1, numx + cntx + 1) - (numx + 1);
        sort(numy + 1, numy + cnty + 1);
        int toty = unique(numy + 1, numy + cnty + 1) - (numy + 1);
        int cnt = 0;
        for(int i = 1; i <= (totx << 1); ++i){
            for(int j = 1; j <= (toty << 1); ++j){
                num[i][j] = ++cnt;
                sum[i][j] = 0;
            }
        }
        D.init(cnt + 5);
        int id;
        for(int i = 1; i <= n; ++i){
            id = lower_bound(numx + 1, numx + 1 + totx, a[i].x1) - numx;
            a[i].x1 = id * 2 - 1;
            id = lower_bound(numx + 1, numx + 1 + totx, a[i].x2) - numx;
            a[i].x2 = id * 2 - 1;
            id = lower_bound(numy + 1, numy + 1 + toty, a[i].y1) - numy;
            a[i].y1 = id * 2 - 1;
            id = lower_bound(numy + 1, numy + 1 + toty, a[i].y2) - numy;
            a[i].y2 = id * 2 - 1;
            for(int j = a[i].x1;  j <= a[i].x2; ++j){
                ++sum[j][a[i].y1], --sum[j][a[i].y2 + 1];
            }
        }
        id = lower_bound(numx + 1, numx + 1 + totx, ax) - numx;
        ax = 2 * id - 1;
        id = lower_bound(numx + 1, numx + 1 + totx, bx) - numx;
        bx = 2 * id - 1;
        id = lower_bound(numy + 1, numy + 1 + toty, ay) - numy;
        ay = 2 * id - 1;
        id = lower_bound(numy + 1, numy + 1 + toty, by) - numy;
        by = 2 * id - 1;
        for(int i = 1; i <= (totx << 1); ++i){
            for(int j = 1; j <= (toty << 1); ++j){
                sum[i][j] = sum[i][j] + sum[i][j - 1];
            }
        }
        int len, v;
        for(int i = 1; i <= (totx << 1); i += 2){
            for(int j = 1; j <= (toty << 1); j += 2){
                for(int k = 0; k < 4; ++k){
                    int x = i + dir[k][0] * 2, y = j + dir[k][1] * 2;
                    if(x < 0 || x > (totx << 1) || y < 0 || y > (toty << 1)) continue ;
                    if(x < i) len = numx[(i + 1) >> 1] - numx[i >> 1];
                    if(x > i) len = numx[(x + 1) >> 1] - numx[x >> 1];
                    if(y < j) len = numy[(j + 1) >> 1] - numy[j >> 1];
                    if(y > j) len = numy[(y + 1) >> 1] - numy[y >> 1];
                    v = sum[i + dir[k][0]][j + dir[k][1]] + 1;
                    D.addedge(num[i][j], num[x][y], (double)len / v);
                    D.addedge(num[x][y], num[i][j], (double)len / v);
                }
            }
        }
        int s = num[ax][ay];
        int t = num[bx][by];
        D.dijkstra(s);
        printf("%.5f\n", D.d[t]);
    }
    return 0;
}