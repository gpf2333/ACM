#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct Query_node{
    int l, r, val, op;
}q[maxn];

int n, m, tot;
int a[maxn], b[maxn << 2];
int getid(int x){
    return lower_bound(b + 1, b + 1 + tot, x) - b;
}

inline int lowbit(int x){
    return x & (-x);
}

struct PrimerTree{
    struct Node{
        int l, r, sum;
    }tree[maxn * 400];
    int ct, sz;
    int rt[maxn], rt1[maxn];
    int q1[maxn], q2[maxn];
    int tot1, tot2;
    void init(){
        ct = 0;
        memset(rt, 0, sizeof(rt));
        memset(rt1, 0, sizeof(rt1));
    }

    void update(int &now, int old, int L, int R, int pos, int val){
        tree[++ct] = tree[old];
        tree[ct].sum += val;
        now = ct;
        if(L == R) return ;
        int mid = (L + R) >> 1;
        if(pos <= mid) update(tree[now].l, tree[old].l, L, mid, pos, val);
        else update(tree[now].r, tree[old].r, mid + 1, R, pos, val);
    }

    int query(int l, int r, int L, int R, int k){
        if(L == R) return L;
        int mid = (L + R) >> 1;
        int sum = tree[tree[r].l].sum - tree[tree[l].l].sum;
        for(int i = 1; i <= tot1; ++i){
            sum -= tree[tree[q1[i]].l].sum;
        }
        for(int i = 1; i <= tot2; ++i){
            sum += tree[tree[q2[i]].l].sum;
        }
        if(sum >= k){
            for(int i = 1; i <= tot1; ++i){
                q1[i] = tree[q1[i]].l;
            }
            for(int i = 1; i <= tot2; ++i){
                q2[i] = tree[q2[i]].l;
            }
            return query(tree[l].l, tree[r].l, L, mid, k);
        }else{
            for(int i = 1; i <= tot1; ++i){
                q1[i] = tree[q1[i]].r;
            }
            for(int i = 1; i <= tot2; ++i){
                q2[i] = tree[q2[i]].r;
            }
            return query(tree[l].r, tree[r].r, mid + 1, R, k - sum);
        }
    }

    int Query(int l, int r, int k){
        tot1 = tot2 = 0;
        int pos = l - 1;
        while(pos){
            q1[++tot1] = rt1[pos];
            pos -= lowbit(pos);
        }
        pos = r;
        while(pos){
            q2[++tot2] = rt1[pos];
            pos -= lowbit(pos);
        }
        return query(rt[l - 1], rt[r], 1, sz, k); //index
    }

    void Update(int a[], int pos, int val){
        int x = val, y = a[pos];
        a[pos] = x;
        while(pos <= n){
            update(rt1[pos], rt1[pos], 1, sz, getid(y), -1);
            update(rt1[pos], rt1[pos], 1, sz, getid(x), 1);
            pos += lowbit(pos);
        }
    }

}pt;

int main(){
    // int T;
    // scanf("%d", &T);
    // while(T--){
        
    // }
    pt.init();
    scanf("%d%d", &n, &m);
    tot = 0;
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
        b[++tot] = a[i];
    }
    char op[10];
    for(int i = 1; i <= m; ++i){
        scanf("%s", op);
        if(op[0] == 'Q'){
            scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].val);
            q[i].op = 1;
        }else{
            scanf("%d%d", &q[i].l, &q[i].val);
            q[i].op = 0;
            b[++tot] = q[i].val;
        }
    }
    sort(b + 1, b + tot + 1);
    tot = unique(b + 1, b + tot + 1) - (b + 1);
    pt.sz = tot;
    for(int i = 1; i <= n; ++i){
        pt.update(pt.rt[i], pt.rt[i - 1], 1, pt.sz, getid(a[i]), 1);
    }
    for(int i = 1; i <= m; ++i){
        if(q[i].op){
            printf("%d\n", b[pt.Query(q[i].l, q[i].r, q[i].val)]);
        }else{
            pt.Update(a, q[i].l, q[i].val);
        }
    }
    return 0;
}