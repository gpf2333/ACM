#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<int, int>mp;
int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

int getphi(int n){
    if(mp.count(n)) return mp[n];
    int res = n, x = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            res -= res / i;
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1) res -= res / n;
    mp[x] = res;
    return res;
}

int dfs(int n, int p){
    if(n == 0) return 1;
    if(p == 1) return 0; 
    return qpow(3, dfs(n - 1, getphi(p)) % getphi(p) + getphi(p),  p);
}

int main(){
    mp.clear();
    int T;
    int mod = 1071017;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        printf("%d\n", dfs(n, mod));
    }
    return 0;
}