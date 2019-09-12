/*
给出一个主串S
查询区间[l, r]字符构成的子串t在主串中第k次出现的位置, 不存在则输出-1.

思路：
1）首先利用后缀数组的height数组建立一棵维护区间[l, r]最长公共前缀的线段树tree。
2）再寻找子串t可能出现初始位置在的sa数组中对应的左边界ql和右边界qr。 
3）再利用主席树寻找[ql, qr]排名第k小sa即为所求。

1) 第一步显然直接建立线段是就可。
2) 第二步利用查询的[l, r]中l位置开头对应的后缀rk[l]
一个可行的t的左边界ql其后缀排名显然是不会超过rk[l]并且[ql, rk[l]]的最长公共前缀lcp应该大于等于x。
一个可行的右边界qr其后缀排名应该要大于等于rk[l]并且[rk[l], qr]的最长公共前缀lcp也应该大于等于x。
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int INF = 0x3f3f3f3f;
struct SuffixArray{
    char s[maxn];
    int sa[maxn], rk[maxn], tp[maxn],c[maxn],height[maxn];

    void radixsort(int n, int m){
        for(int i = 0; i <= m; ++i) c[i] = 0;
        for(int i = 1; i <= n; ++i) ++c[rk[i]];
        for(int i = 1; i <= m; ++i) c[i] += c[i - 1];
        for(int i = n; i >= 1; --i) sa[c[rk[tp[i]]]--] = tp[i];
    }

    void build_sa(int n, int m){
        for(int i = 1; i <= n; ++i){
            rk[i] = s[i], tp[i] = i;
        }
        radixsort(n, m);
        for(int k = 1; k <= n; k <<= 1){
            int p = 0;
            for(int i = n - k + 1; i <= n; ++i) tp[++p] = i;
            for(int i = 1; i <= n; ++i){
                if(sa[i] > k) tp[++p] = sa[i] - k;
            }
            radixsort(n, m);
            std::swap(rk, tp);
            p = rk[sa[1]] = 1;
            for(int i = 2; i <= n; ++i){
                rk[sa[i]] = (tp [sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i - 1] + k]) ? p : ++p;
            }
            if(p >= n) break;
            m = p;
        }
        int k = 0;
        for(int i = 1; i <= n; ++i){
            if(k) --k;
            int j = sa[rk[i] - 1];
            while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;
        }
    }
}sa;

#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
struct SegmentTree{
    int l, r;
    int val;
}tree[maxn << 4];

inline void pushup(int rt){
    tree[rt].val = min(tree[lson].val, tree[rson].val);
}

void build(int L, int R, int rt){
    tree[rt].l = L, tree[rt].r = R;
    if(L == R){
        tree[rt].val = sa.height[L];
        return ;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

//[1, r] find(x)
int query_l(int r, int x, int rt){
    if(tree[rt].r <= r){
        if(tree[rt].val >= x) return -1;
        if(tree[rt].l == tree[rt]. r) return tree[rt].l;
        if(tree[rson].val >= x){
            return query_l(r, x, lson);
        }else{
            return query_l(r, x, rson);
        }
    }else{
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        int res = query_l(r, x, lson);
        if(mid >= r) return res;
        return max(res, query_l(r, x, rson));
    }
}

//[l, n] find(x)
int query_r(int l, int x, int rt){
    if(tree[rt].l >= l){
        if(tree[rt].val >= x) return INF;
        if(tree[rt].l == tree[rt]. r) return tree[rt].l;
        if(tree[lson].val >= x){
            return query_r(l, x, rson);
        }else{
            return query_r(l, x, lson);
        }
    }else{
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        int res = query_r(l, x, rson);
        if(mid < l) return res;
        return min(res, query_r(l, x, lson));
    }
}

struct Tsgment{
    struct node{
        int ls, rs, sum;
    }ns[maxn * 40];
    int ct;
    int rt[maxn * 40];

    void cpy(int& now, int old) {
        now = ++ct;
        ns[now] = ns[old];
    }

    void pushUp(int& now) {
        ns[now].sum = ns[ns[now].ls].sum + ns[ns[now].rs].sum;
    }

    void build(int& now, int l, int r) {
        now = ++ct;
        ns[now].sum = 0;
        if (l == r) return;
        int m = (l + r) >> 1;
        build(ns[now].ls, l, m);
        build(ns[now].rs, m + 1, r);
    }

    void update(int& now, int old, int l, int r, int x) {
        cpy(now, old);
        if (l == r) {
            ns[now].sum++;
            return;
        }
        int m = (l + r) >> 1;
        if (x <= m) update(ns[now].ls, ns[old].ls, l, m, x);
        else update(ns[now].rs, ns[old].rs, m + 1, r, x);
        pushUp(now);
    }

    int query(int s, int t, int l, int r, int k){
        if (l == r) return l;
        int m = (l + r) >> 1;
        int cnt = ns[ns[t].ls].sum - ns[ns[s].ls].sum;
        if (k <= cnt) return query(ns[s].ls, ns[t].ls, l, m, k);
        return query(ns[s].rs, ns[t].rs, m + 1, r, k - cnt);
    }

    void init(int n){
        ct = 0;
        build(rt[0], 1, n);
    }
}ts;

int main(){
    int T, n, q;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &q);
        scanf("%s", sa.s + 1);
        sa.build_sa(n, 128);
        ts.init(n);
        for(int i = 1; i <= n; ++i){
            ts.update(ts.rt[i], ts.rt[i - 1], 1, n, sa.sa[i]);
        }
        build(1, n, 1);
        while(q--){
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int ql = query_l(sa.rk[l], r - l + 1, 1);
            ql = (ql == -1) ? 1 : ql;
            int qr;
            if(sa.rk[l] == n){
                qr = n;
            }else{
                qr = query_r(sa.rk[l] + 1, r - l + 1, 1);
                qr = (qr == INF) ? n : --qr;
            }
            if(qr - ql + 1 < k){
                puts("-1"); continue ;
            }else{
                printf("%d\n", ts.query(ts.rt[ql - 1], ts.rt[qr], 1, n, k));
            }
        }
    }
}