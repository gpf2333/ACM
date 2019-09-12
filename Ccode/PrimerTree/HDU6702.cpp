/*
由于查询的元素只会在[1,n+1]内出现，因此我们可以把+1e7看成删除了，因为我们最多的答案只会是n+1.
对于每个删除的元素，将其插入到set中，查询的时候，查询[r+1,n+1]中第一个>=k的元素，再和set中第一个>=k的元素相比较，
选择最小的即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
struct PrimerTree{
    struct Node{
        int ls, rs, sum;
    }tree[maxn * 20];
    int ct;
    int sz; // 
    int rt[maxn * 20];

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

    //find k_th
    // int query(int l, int r, int L, int R, int k){
    //     if(L == R) return L;
    //     int mid = (L + R) >> 1;
    //     int cnt = tree[tree[r].ls].sum - tree[tree[l].ls].sum;
    //     if(k <= cnt) return query(tree[l].ls, tree[r].ls, L, mid, k);
    //     else return query(tree[l].rs, tree[r].rs, mid + 1, R, k - cnt);
    // }

    // find(x) first x >= k
    int query(int l, int r, int L, int R, int k){
        if(L == R) return L;
        int mid = (L + R) >> 1;
        int cntl = tree[tree[r].ls].sum - tree[tree[l].ls].sum;
        int res = INF;
        if(mid >= k && cntl){
            res = query(tree[l].ls, tree[r].ls, L, mid,  k);
        }
        if(res != INF) return res;
        int cntr = tree[tree[r].rs].sum - tree[tree[l].rs].sum;
        if(cntr){
            res = query(tree[l].rs, tree[r].rs, mid + 1, R, k);
        }
        return res;
    }

    void init(int n){
        ct = 0;
        sz = n; //note!!!
        build(rt[0], 1, n);
    }

    int Query(const int l, const int r, const int k){ 
        return query(rt[l - 1], rt[r], 1, sz, k);
    }

}pt;

set<int>s;
int a[maxn];
int main(){
    int T, n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        pt.init(n + 1);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            pt.update(pt.rt[i], pt.rt[i - 1], 1, pt.sz, a[i]);
        }
        pt.update(pt.rt[n + 1], pt.rt[n], 1, pt.sz, n + 1);
        s.clear();
        int ans = 0;
        int op, pos, t1, t2, t3;
        while(m--){
            scanf("%d", &op);
            if(op == 1){
                scanf("%d", &t1);
                pos = ans ^ t1;
                s.insert(a[pos]);
            }else{
                scanf("%d%d", &t2, &t3);
                int r = t2 ^ ans, k = t3 ^ ans;
                ans = pt.Query(r + 1, n + 1, k);
                if(s.size() > 0){
                    auto it = s.lower_bound(k);
                    if(it != s.end()) ans = min(ans, *it);
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}