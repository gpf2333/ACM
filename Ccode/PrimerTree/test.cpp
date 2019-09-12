//静态区间第k小主席树
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 2e5 + 10;
struct PrimerTree{
    struct Node{
        int ls, rs, sum;
    }tree[maxn * 40]; //32 or 40
    int ct;
    int sz; // 
    int rt[maxn * 40];

    inline void cpy(int&now, int old){
        now = ++ct;
        tree[now] = tree[old];
    }

    inline void pushup(const int& now){
        tree[now].sum = tree[tree[now].ls].sum + tree[tree[now].rs].sum;
    }

    void build(int&now, int L, int R){
        now = ++ct;
        tree[now].sum = 0;
        if(L == R) return ;
        int mid = (L + R) >> 1;
        build(tree[now].ls, L, mid);
        build(tree[now].rs, mid + 1, R);
    }

    void update(int &now, int old, int L, int R, int val){
        cpy(now, old);
        if(L == R){
            ++tree[now].sum;
            return ;
        }    
        int mid = (L + R) >> 1;
        if(val <= mid) update(tree[now].ls, tree[old].ls, L, mid, val);
        else update(tree[now].rs, tree[old].rs, mid + 1, R, val);
        pushup(now);
    }

    int query(int l, int r, int L, int R, int k){
        if(L == R) return L;
        int mid = (L + R) >> 1;
        int cnt = tree[tree[r].ls].sum - tree[tree[l].ls].sum;
        if(k <= cnt) return query(tree[l].ls, tree[r].ls, L, mid, k);
        else return query(tree[l].rs, tree[r].rs, mid + 1, R, k - cnt);
    }

    void init(int n){
        ct = 0;
        build(rt[0], 1, n);
    }

    void Hash(int n, int a[], int b[]){
        for(int i = 1; i <= n; ++i) b[i] = a[i];
        sort(b + 1, b + n + 1);
        sz = unique(b + 1, b + n + 1) - (b + 1);
        init(sz);
        for(int i = 1; i <= n; ++i){
            a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
            update(rt[i], rt[i - 1], 1, sz, a[i]);
        }
    }

    int Query(const int l, const int r, const int k){ 
        return query(rt[l - 1], rt[r], 1, sz, k); //hash of index in b
    }

}pt;

int a[maxn], b[maxn];
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
    }
    pt.Hash(n, a, b);
    while(m--){
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", b[pt.Query(l, r, k)]);
    }
    return 0;
}