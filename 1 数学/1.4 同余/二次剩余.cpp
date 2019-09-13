#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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

//注意n % p的特殊情况
int Sqrt(int n, int p){
    if(n % p == 0) return p;
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
    int T, n, p;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &p);
        n %= p;
        int x1 = Sqrt(n, p);
        if(x1 == -1){
            puts("No root"); continue ;
        }
        int x2 = p - x1;
        if(x1 > x2) swap(x1, x2);
        if(x1 == x2){
            printf("%d\n", x1);
        }else{
            printf("%d %d\n", x1, x2);
        }
    }
    return 0;
}