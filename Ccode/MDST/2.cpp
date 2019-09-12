#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 10000 + 50;
const double INF = 0x3f3f3f3f;
struct Edge{
    int x, y;
    double w;
}edge[maxn];
double in[maxn];
int vis[maxn], id[maxn],pre[maxn];
double zhuliu(int root, int n, int m){
    double res = 0;
    while(true){
        for(int i = 0; i < n; ++i) in[i] = INF;
        for(int i = 0; i < m; ++i){
            int x = edge[i].x;
            int y = edge[i].y;
            if(edge[i].w < in[y] && x != y){
                pre[y] = x;
                in[y] = edge[i].w;
            }
        }

        for(int i = 0; i < n; ++i){
            if(i == root) continue;
            if(in[i] == INF) return - 1;
        }

        int cnt = 0;
        in[root] = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        for(int i = 0; i < n; ++i){
            res += in[i];
            int y = i;
            while(vis[y] != i && id[y] == -1 && y != root){
                vis[y] = i;
                y = pre[y];
            }
            if(y != root && id[y] == -1){
                for(int x = pre[y]; x != y; x = pre[x]) id[x] = cnt;
                id[y] = cnt++;
            }
        }
        if(cnt == 0) break ;

        for(int i = 0; i < n; ++i){
            if(id[i] == - 1) id[i] = cnt++;
        } 
        for(int i = 0; i < m; ++i){
            int x = edge[i].x;
            int y = edge[i].y;
            edge[i].x = id[x];
            edge[i].y = id[y];
            if(id[x] != id[y]) edge[i].w -= in[y];
        }
        n = cnt;
        root = id[root];
    }
    return res;
}
struct Node{
    double x, y;
}p[maxn];

double getdis(const Node &a, const Node &b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
};

int main(){
    int n, m;
    while(~scanf("%d%d",&n,&m)){
        if(!n&&!m) break ;
        for(int i = 0; i < n; ++i){
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        for(int i = 0; i < m; ++i){
            scanf("%d%d",&edge[i].x, &edge[i].y);
            --edge[i].x;
            --edge[i].y;
            if(edge[i].x != edge[i].y){
                edge[i].w = getdis(p[edge[i].x], p[edge[i].y]);
            }else{
                edge[i].w = INF;
            }
        }
        double res = zhuliu(0, n, m);
        if(res == - 1){
            puts("poor snoopy");
        }else{
            printf("%.2f\n", res);
        }
    }
    return 0;
}