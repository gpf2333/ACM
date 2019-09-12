#include<bits/stdc++.h>
using namespace std;
const int maxn = 500000 + 50;

int n;
int a[maxn];
int bit[maxn];
int vis[1000050];

inline int lowbit(const int x){
    return x & (-x);
}

void add(int x, int val){
    while(x <= n){
        bit[x] += val;
        x += lowbit(x);
    }
}

int getsum(int x){
    int res = 0;
    while(x > 0){
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

struct Node{
    int pos, l, r;
}q[maxn];

inline bool cmp(const Node &a, const Node &b){
    return a.r < b.r;
}

int ans[maxn];

int main(){
    memset(bit, 0, sizeof(bit));
    memset(vis, 0, sizeof(vis));
    int m;
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].pos = i;
    }
    sort(q, q + m, cmp);
    int nex = 1;
    for(int i = 0; i < m; ++i){
        for(int j = nex; j <= q[i].r; ++j){
            if(vis[a[j]]){
                add(vis[a[j]], -1);
            }
            add(j, 1);
            vis[a[j]] = j;
        }
        nex = q[i].r + 1;
        ans[q[i].pos] = getsum(q[i].r) - getsum(q[i].l - 1);
    }
    for(int i = 0; i < m; ++i){
        printf("%d\n", ans[i]);
    }
    return 0;
}