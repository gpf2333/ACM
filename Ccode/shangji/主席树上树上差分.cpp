#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct node{
    int u, v, w;
}e[maxn];

struct Edge{
    int to, next, w;
}edge[maxn << 2];

int tot, head[maxn];
int dp[maxn][21];

void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1;
        for(int j = 0; j <= 20; ++j){
            dp[i][j] = 0;
        }
    }
}

inline void addedge(int u, int v, int w){
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}
struct TREE
{
    int l, r;
    int val;
}tree[maxn * 21];

int val[maxn], len;
int deep[maxn];
int root[maxn];
int cnt;

int build(int l ,int r, int rt){
    int cur = ++cnt;
    tree[cur] = tree[rt];
    if(l == r) return cur;
    int mid = (r + l) >> 1;
    tree[cur].l = build(l, mid, tree[rt].l);
    tree[cur].r = build(mid + 1, r, tree[rt].r);
    return cur;
}

int update(int pos, int l, int r, int rt){
    int cur = ++cnt;
    tree[cur] = tree[rt];
    ++tree[cur].val;
    if(l == r) return cur;
    int mid = (l + r) >> 1;
    if(pos <= mid) tree[cur].l = update(pos, l, mid, tree[rt].l);
    else tree[cur].r = update(pos, mid + 1, r, tree[rt].r);
    return cur;
}

void dfs(int u, int fa){
    deep[u] = deep[fa] + 1;
    dp[u][0] = fa;
    for(int i = 1; i <= 20; ++i){
        if(dp[u][i-1]){
            dp[u][i] = dp[dp[u][i - 1]][i-1];
        } else {
            break ;
        }
    }
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa) continue ;
        root[v] = update(edge[i].w,  1,  len,  root[u]);
        dfs(v, u);
    }
}

int lca(int u, int v){
    if(deep[u] < deep[v]) swap(u, v);
    int tmp = deep[u] - deep[v];
    for(int i = 0; i <= 20; ++i){
        if(tmp & (1 << i)){
            u = dp[u][i];
        }
    }
    if(u == v) return u;
    for(int i  = 20; i >= 0; --i){
        if(dp[u][i] != dp[v][i]){
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0];
}

int query(int l, int r, int u, int v, int x, int val){
    if(r <= val){
        return tree[u].val + tree[v].val - 2 * tree[x].val;
    }
    int res = 0;
    int mid = (l + r) >> 1;
    res += query(l, mid, tree[u].l, tree[v].l, tree[x].l, val);
    if(val > mid)
    res += query(mid + 1, r, tree[u].r, tree[v].r, tree[x].r, val);
    return res;
}

int main(){
    int n, q;
    while(~scanf("%d%d", &n, &q)){
        init(n);
        int u, v, w;
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
            val[i] = e[i].w;
        }
        sort(val + 1, val + n);
        len = unique(val + 1, val + n) - val - 1;
        for(int i = 1; i < n; ++i){
            w = lower_bound(val + 1, val + 1 + len, e[i].w) - val;
            addedge(e[i].u, e[i].v, w);
            addedge(e[i].v, e[i].u, w);
        }
        cnt = 0;
        root[0] = build(1, len, 0);
        dfs(1, 0);
        int k;
        while(q--){
            scanf("%d%d%d", &u, &v, &k);
            k = upper_bound(val + 1, val + 1 + len, k) - val - 1;
            if(k == 0){
                puts("0");
                continue ;
            }
            printf("%d\n", query(1, len, root[u], root[v], root[lca(u,v)], k));
        }
    }
    return 0;
}