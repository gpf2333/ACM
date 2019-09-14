
//下标从1开始的后缀数组模板
const int maxn = 1e5 + 100;
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

    inline int lcp(int l, int r){ //查询以后缀中从l和以开始和r开始的后缀的最长公共前缀lcp
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
