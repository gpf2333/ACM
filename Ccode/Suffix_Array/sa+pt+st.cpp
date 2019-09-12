#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int INF = 0x3f3f3f3f;
struct SuffixArray{
    char s[maxn];
    int sa[maxn], rk[maxn], tp[maxn],c[maxn],height[maxn];
    int n;
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

    int dp[maxn][20];
    void init_rmq(int n){
        for(int i = 1; i <= n; ++i){
            dp[i][0] = height[i];
        }
        for(int j = 1; (1 << j) <= n; ++j){
            for(int i = 1; i + (1 << j) - 1 <= n; ++i){
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    inline int rmq(int l, int r){
        int k = 31 - __builtin_clz(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }

    inline int lcp(int l, int r){
        l = rk[l], r = rk[r];
        if(l > r) swap(l , r);
        if(l == r) return n - sa[l] + 1;
        return rmq(l + 1, r);
    }

    int query_l(int L, int R, int n){
        int len = R - L + 1;
        int l = 1, r = rk[L], ans = rk[L];
        while(l <= r){
            int mid = (l + r) >> 1;
            if(lcp(sa[mid], L) >= len){
                ans = mid, r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        return ans;
    }

    int query_r(int L, int R, int n){
        int len = R - L + 1;
        int l = rk[L], r = n, ans = rk[L];
        while(l <= r){
            int mid = (l + r) >> 1;
            if(lcp(L, sa[mid]) >= len){
                ans = mid, l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        return ans;
    }
}sa;

struct PrimerTree{
    struct Node{
        int ls, rs, sum;
    }tree[maxn * 32]; //32 or 40
    int ct;
    int sz; // 
    int rt[maxn * 32];

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
        sz = n;
        build(rt[0], 1, n);
    }

    int Query(const int l, const int r, const int k){ 
        return query(rt[l - 1], rt[r], 1, sz, k);
    }

}pt;

int main(){
    int T, n, q;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &q);
        scanf("%s", sa.s + 1);
        sa.n = n;
        sa.build_sa(n, 128);
        sa.init_rmq(n);
        pt.init(n);
        for(int i = 1; i <= n; ++i){
            pt.update(pt.rt[i], pt.rt[i - 1], 1, pt.sz, sa.sa[i]);
        }
        while(q--){
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int ql = sa.query_l(l, r, n);
            int qr = sa.query_r(l, r, n); 
            if(qr - ql + 1 < k){
                puts("-1"); 
                continue ;
            }else{
                printf("%d\n", pt.Query(ql, qr, k));
            }
        }
    }
}