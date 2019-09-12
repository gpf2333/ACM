#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long ll;
int a[maxn]; //note a!
struct PrimerTree{
    struct Node{
        int l, r;
        int tag;
        ll sum;
    }tree[maxn * 30];
    int ct = 0, sz;
    int now = 0; //当前时间
    int rt[maxn];
    void build(int L, int R, int &rt){
        rt = ++ct; 
        tree[rt].l = tree[rt].r = tree[rt].tag = 0; //note, mistake
        if(L == R){
            tree[rt].sum = a[L]; //note a!    
            return ;
        }
        int mid = (L + R) >> 1;
        build(L, mid, tree[rt].l);
        build(mid + 1, R, tree[rt].r);
        tree[rt].sum = tree[tree[rt].l].sum + tree[tree[rt].r].sum;
    }
    void update(int &now, int old, int L, int R, int l, int r, int val){
        tree[now = ++ct] = tree[old];
        if(l <= L && R <= r){
            tree[now].tag += val;
            tree[now].sum += (ll)(R - L + 1) * val;
            return ;
        }
        int mid = (L + R) >> 1;
        if(l <= mid) update(tree[now].l, tree[old].l, L, mid, l, r, val);
        if(r > mid) update(tree[now].r, tree[old].r, mid + 1, R, l, r, val);
        tree[now].sum = tree[tree[now].l].sum + tree[tree[now].r].sum + (ll)(R - L + 1) * tree[now].tag;
    }
    ll query(int l, int r, int pre, int L, int R, int rt){
        if(l <= L && R <= r){
            return tree[rt].sum + (ll)pre * (R - L + 1);
        }
        int mid = (L + R) >> 1;
        ll res = 0;
        if(l <= mid){
            res += query(l, r, pre + tree[rt].tag, L, mid, tree[rt].l);
        }
        if(r > mid){
            res += query(l, r, pre + tree[rt].tag, mid + 1, R, tree[rt].r);
        }
        return res;
    }
    //初始化线段树
    inline void init(int n){
        ct = now = 0, sz = n;
        build(1, sz, rt[0]);
    }
    //时间倒流，重置历史版本线段树
    inline void settime(int t){
        now = t;
    }
    //区间更改，时间前进
    inline void Update(int l, int r, int val){
        update(rt[now + 1], rt[now], 1, sz, l, r, val);
        ++now;
    }
    //区间求和查询
    ll Query(int l, int r){
        return query(l, r, 0, 1, sz, rt[now]);
    }
    //历史版本区间求和查询
    ll Query_t(int l, int r, int t){
        return query(l, r, 0, 1, sz, rt[t]);    
    }
}pt;

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        pt.init(n);
        char op[5];
        int l, r, t, val;
        while(m--){
            scanf("%s", op);
            if(op[0] == 'B'){
                scanf("%d", &t);
                pt.settime(t);
            }else if(op[0] == 'C'){
                scanf("%d%d%d", &l, &r, &val);
                pt.Update(l, r, val);
            }else if(op[0] == 'Q'){
                scanf("%d%d", &l, &r);
                printf("%lld\n", pt.Query(l, r));
            }else if(op[0] == 'H'){
                scanf("%d%d%d", &l, &r, &t);
                printf("%lld\n", pt.Query_t(l, r, t));
            }
        }
    }
}