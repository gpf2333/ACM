#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 100;
const int INF = 0x3f3f3f3f;

int sum[maxn << 2];
inline int lowbit(int x){
    return x & (-x);
}

void add(int x, int v){
    while(x < maxn){
        sum[x] += v;
        x += lowbit(x);
    }
}

int query(int x){
    int res = 0;
    while(x){
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

struct Node{
    int id, u, v, w, flag;
}q[maxn << 1];

inline bool cmp(Node &a, Node &b){
    if(a.w == b.w){
        return a.flag < b.flag;
    }
    return a.w < b.w;
}

struct Edge{
    int to, next, w;
}edge[maxn << 1];
int tot, head[maxn];
int dfs_clock;
int siz[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], id[maxn];

void init(int n){
    tot = dfs_clock = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = son[i] = -1;
    }
}

inline void addedge(int u, int v, int w){
    edge[tot] = {v, head[u], w};
    head[u] = tot++;
}

void dfs1(int u, int pa, int d){
    dep[u] = d, fa[u] = pa, siz[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == pa) continue ;
        q[v] = {v, v, u, edge[i].w, 0};
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[v] > siz[son[u]]){
            son[u] = v;
        }
    }
}

void dfs2(int u, int t){
    top[u] = t, id[u] = ++dfs_clock;
    if(son[u] == -1) return ;
    dfs2(son[u], t);
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u]){
            dfs2(v, v);
        }
    }
}

//note!!!
void update_path(int x, int y){
    if(dep[top[x]] < dep[top[y]]){
        swap(x, y);
    }
    add(id[x], 1);
}

int query_path(int x, int y){
    int res = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += (query(id[x]) - query(id[top[x]] - 1)); // note
        x = fa[top[x]];
    }
    if(x == y) return res;
    if(dep[x] > dep[y]) swap(x, y);
    res += query(id[y]) - query(id[son[x]] - 1); // note!!! this is not segment tree
    return res;
}

int ans[maxn];
int main(){
    int n, m, u, v, w;
    scanf("%d%d",&n,&m);
    init(n); // note
    memset(sum, 0, sizeof(sum)); // importenat
    for(int i = 1; i < n; ++i){
        scanf("%d%d%d",&u,&v,&w);
        addedge(u, v, w);
        addedge(v, u, w);
        q[i].flag = 0;
    }
    q[1] = {1, 1, 1, INF, 0};
    dfs1(1, 0, 1);
    dfs2(1, 1);
    for(int i = 1; i <= m; ++i){
        scanf("%d%d%d",&u,&v,&w);
        q[i + n] = {i + n, u, v, w, 1};
    }
    int up = n + m + 1;
    sort(q + 1, q + up, cmp);
    for(int i = 1; i < up; ++i){
        if(!q[i].flag){
            update_path(q[i].u, q[i].v);
        }else{
            ans[q[i].id - n] = query_path(q[i].u, q[i].v);
        }
    }
    for(int i = 1; i <= m; ++i){
        printf("%d\n", ans[i]);
    }
    return 0;
}
