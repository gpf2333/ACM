#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 2e3 + 5;

int x[maxn], y[maxn];

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

int Lagrange(int n, int x[], int y[], int pos){
    int ans = 0;
    for(int i = 0; i <= n; ++i){ //n + 1 power
        int up = 1, down = 1;
        for(int j = 0; j <= n; ++j){
            if(i != j){
                up = (ll)up * (pos - x[j]) % mod;
                down = (ll)down *(x[i] - x[j]) % mod;
            }
        }
        ans =(ans + (ll)y[i] * up % mod * (ll)qpow(down, mod - 2, mod) % mod) % mod;
    }
    ans = (ans + mod) % mod;
    return ans;
}

int main(){
    int n, k;
    while(~scanf("%d%d", &n, &k)){
        for(int i = 0; i < n; ++i){
            scanf("%d%d", &x[i], &y[i]);
        }
        printf("%d\n", Lagrange(n - 1, x, y, k));
    }
    return 0;
}