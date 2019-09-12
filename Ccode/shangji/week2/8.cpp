#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
typedef int Weighttype;
struct Edge{
    int from, to, next;
    Weighttype w;
}edge[maxn << 1];
int tot, head[maxn];
bool vis[maxn];
vector<vector<int> >G(maxn);
void init(){
    tot = 0;
    memset(head, -1, sizeof(head));
}

inline void addedge(const int u, const int v, const int w){
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].w = w;
    head[u] = tot++;
}

int len;
int path[maxn];
void dfs(int u, int ed){
    vis[u] = true;
    if(u == ed){
        for(int i = 0; i < len; ++i){
            printf("%d ", path[i]);
        }
        puts("");
        return ;
    }
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(!vis[v]){
            path[len++] = v;
            dfs(v, ed);
            len--;
            vis[v] = false;
        }
    }
    return ;
}


void solve(const int n, const int m,  int indegree[]){
    Weighttype *ve = new Weighttype[n + 1];
    Weighttype *vl = new Weighttype[n + 1];
    queue<int>q;
    stack<int>s;
    for(int i = 0; i < n; ++i){
        ve[i] = 0;
    }
    for(int i = 0; i < n; ++i){
        if(indegree[i] == 0){
            q.push(i);
        }
    }
    int cnt = 0;
    int st = 0;
    if(!q.empty()) st = q.front();
    while(!q.empty()){
        int u = q.front();
        q.pop();
        s.push(u);
        ++cnt;
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if((--indegree[v]) == 0){
                q.push(v);
            }
            if(ve[u] + edge[i].w > ve[v]){
                ve[v] = ve[u] + edge[i].w;
            }
        }
    }
    if(cnt < n){
        delete []ve;
        delete []vl;
        puts("circle!");
        return ;
    }
    int ed = s.top(); 
    s.pop();
    for(int i = 0; i < n; ++i){
        vl[i] = ve[ed];
    }
    while(!s.empty()){
        int u = s.top();
        s.pop();
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(vl[v] -  edge[i].w < vl[u]){
                vl[u] = vl[v] - edge[i].w;
            }
        }
    }
    Weighttype *e = new Weighttype[m + 1];
    Weighttype *l = new Weighttype[m + 1];
    for(int u = 0; u < n; ++u){
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            e[i] = ve[u];
            l[i] = vl[v] - edge[i].w;
        }
    }
    printf("vetrix: ");
    for(int i = 0; i < n; ++i){
        printf("%d ", i);
        G[i].clear();
        vis[i] = false;
    }
    printf("\nve:     ");
    for(int i = 0; i < n; ++i){
        printf("%d ", ve[i]);
    }
    printf("\nvl:     ");
    for(int i = 0; i < n; ++i){
        printf("%d ", vl[i]);
    }
    printf("\nedges: \n");
    for(int i = 0; i < tot; ++i){
        printf("(%d, %d), e: %d, l: %d\n", edge[i].from, edge[i].to, e[i], l[i]);
        if(e[i] == l[i]){
            G[edge[i].from].push_back(edge[i].to);
        }
    }
    len = 0;
    path[len++] = st;
    puts("key ways: ");
    dfs(st, ed);
    delete []ve;
    delete []vl;
    delete []e;
    delete []l;
}


int main(){
    ios::sync_with_stdio(false);
    int n, m;
    while(cin >> n >> m){
        init();
        int *indegree = new int[n + 1];
        for(int i = 0; i <= n; ++i){
            indegree[i] = 0;
        }
        int u, v;
        Weighttype w;
        for(int i = 0; i < m; ++i){
            cin >> u >> v >> w;
            addedge(u, v, w);
            ++indegree[v];
        }
        solve(n, m, indegree);
        delete []indegree;
    }
    return 0;
}

/*
7 11
0 1 8
0 4 5
0 3 4
1 2 3
2 6 6
3 4 1
4 1 2
4 2 7
4 5 2
5 2 3
5 6 9
*/