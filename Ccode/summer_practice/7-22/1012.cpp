#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const int mod = (119 << 23 | 1);

ll fast_pow(ll a, ll b, int mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

namespace NTT {
    const int P = (119 << 23 | 1);
    const int G = 3;
    const int NUM = 25;
    int C[maxn << 2];
    int wn[NUM];

    void GetWn(){
        for(int i = 0; i < NUM; ++i){
            wn[i] = fast_pow(G, (P - 1) / (1LL << i), P);
        }
    }

    void change(int y[], int len){
        int up = len - 1;
        for(int i = 1, j = len >> 1; i < up; ++i){
            if(i < j) swap(y[i], y[j]);
            int k = (len >> 1);
            while(j >= k){
                j -= k;
                k >>= 1;
            }
            if(j < k) j += k;
        }
    }

    void NTT(int y[], int len, int on){
        change(y, len);
        for(int h = 2, id = 1; h <= len;  h <<= 1, ++id){
            for(int j = 0; j < len; j += h){
                int w = 1;
                for(int k = j; k < (j + (h >> 1)); ++k){
                    int u = y[k] % P;
                    int t = (1LL * w * (y[k + (h >> 1 )]) % P) % P;
                    y[k] = (u + t) % P;
                    y[k + (h >> 1)] = ((u - t) % P + P) % P;
                    w = (ll)w * wn[id] % P;
                }
            }
        }
        if(on == -1){
            int inv = fast_pow(len, P - 2, P);
            for(int i = 1; i < (len >> 1); ++i){
                swap(y[i], y[len - i]);
            }
            for(int i = 0; i < len; ++i){
                y[i] = (ll)y[i] * inv % P;
            }
        }
    }

    void calc(int A[], int B[], int n, int m){
        int len = 1, up = max(n, m);
        while(len <= (up << 1)) len <<= 1;
        NTT(A, len, 1); 
        NTT(B, len, 1);
        for(int i = 0; i < len; ++i){
            C[i] = ((ll)A[i] * (ll)B[i]) % P;
            A[i] = B[i] = 0;
        }
        NTT(C, len, -1);
    }
};


int a[maxn << 2], c[maxn << 2];
int fac[1100005], invf[1100005];
void init(){
    invf[0] = fac[0] = 1;
    for(int i = 1; i < maxn; ++i){
        fac[i] = (ll)fac[i - 1] * i % mod;
    }
    invf[maxn - 1] = fast_pow(fac[maxn - 1], mod - 2, mod);
    for(int i = maxn - 2; i; --i){
        invf[i] = (ll)invf[i + 1] * (i + 1LL) % mod; 
    }
}

inline int C(int n, int m){
    return (n < m) ? 0 : (ll)fac[n] * invf[n - m] % mod * invf[m] % mod;
}

int main(){
    init();
    NTT::GetWn();
    int T, n, m;
    int cnt[5];
    scanf("%d", &T);
    while(T--){
        memset(cnt, 0, sizeof(cnt));
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
        }
        int x;
        for(int i = 1; i <= m; ++i){
            scanf("%d", &x);
            ++cnt[x];
        }
        for(int i = 1; i <= 3; ++i){
            if(!cnt[i]) continue ;
            memset(c, 0, sizeof(c));
            for(int j = 0; j * i < n; ++j){
                c[j * i] = C(cnt[i] + j - 1, j);
            }
            NTT::calc(a + 1, c, n, n);
            for(int i = 0; i < n; ++i){
                a[i + 1] = NTT::C[i];
            }
        }
        ll ans = 0;
        for(int i = 1; i <= n; ++i){
            ans = ans ^ (1LL * i * a[i]); 
        }
        printf("%lld\n", ans);
    }
    return 0;
}