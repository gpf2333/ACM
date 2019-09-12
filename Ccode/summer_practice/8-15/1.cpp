#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

int w;
struct tf{
    int p, d;
    tf(int pp = 0, int dd = 0):p(pp),d(dd){}
};

inline int Mod(ll a, int p){
    a %= p;
    if(a < 0) a += p;
    return a;
}

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

inline int Legendre(int a, int p){
    return qpow(a, (p - 1) >> 1, p);
}

tf mul(const tf &a, const tf &b, int mod){
    tf ans;
    ans.p =((ll)a.p * b.p % mod + (ll)a.d * b.d % mod * w % mod) % mod;
    ans.d =((ll)a.p * b.d % mod + (ll)a.d * b.p % mod) % mod;
    return ans;
}

tf qpow(tf a, int b, int mod){
    tf res(1, 0);
    while(b > 0){
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

int Sqrt(int n, int p){
    if(p == 2) return 1;
    if(Legendre(n, p) + 1 == p) return -1;
    int a;
    srand(time(0));
    while(1){
        a = rand() % p;
        w = Mod((ll)a * a - n, p);
        if(Legendre(w, p) + 1 == p) break ;
    }
    tf tmp(a, 1);
    tf ans = qpow(tmp, (p + 1) >> 1, p);
    return ans.p;
}

int main(){
    const int p = 1e9 + 7;
    const int inv2 = qpow(2, p - 2, p);
    int T, n;
    int b, c;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &b, &c);
        // scanf("%d%d", &n, &p);
        n = ((ll)b * b % p - 4LL * c) % p;
        n = (n + p) % p;
        int x1 = 0;
        if(n){
            x1 = Sqrt(n, p);
        }
        if(x1 == -1){
            puts("-1 -1"); 
            continue ;
        }
        int x = (ll)(b + x1) % mod * inv2 % mod;
        int y = (b - x + mod) % mod;
        if((ll)x * y % mod == c){
            if(x > y) swap(x, y);
            printf("%d %d\n", x, y);
            continue ;
        }
        x = (ll)(b - x1) % mod * inv2 % mod;
        y = (b - x + mod) % mod;
        if((ll)x * y % mod == c){
            if(x > y) swap(x, y);
            printf("%d %d\n", x, y);
            continue ;
        }else{
            puts("-1 -1");
            continue ;
        }
        // int x2 = p - x1;
        // if(x1 > x2) swap(x1, x2);
        // if(x1 == x2){
        //     printf("%d\n", x1);
        // }else{
        //     printf("%d %d\n", x1, x2);
        // }
    }
    return 0;
}