#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t i128;
const int maxn = 1e5 + 10;

ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y){
    ll d = a;
    if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

bool excrt(ll r[], ll m[], ll n, i128 &re, i128 &mo){
    ll x, y, tmp;
    mo = m[0], re = r[0];
    for(int i = 1; i < n; ++i){
        ll d = exgcd(mo, m[i], x, y);
        if((r[i] - re) % d != 0) return 0;
        x = (r[i] - re) / d * (i128)x % (m[i] / d);
        re += x * mo;
        mo = mo / d * m[i];
        re %= mo;
    }
    re = (re + mo) % mo;
    return 1;
}

char s[128];
template<class T>
void output(T x){
    if(x < 0){
        putchar('-');
        x -= x;
    }
    int cnt = 0;
    if(x == 0){
        putchar('0');
    }
    while(x){
        s[cnt++] = (x % 10) + '0';
        x /= 10;
    }
    for(int i = cnt - 1; ~i; --i){
        putchar(s[i]);
    }
}

ll a[maxn], b[maxn];
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%lld%lld", &a[i], &b[i]);
    }
    i128 re, mo;
    excrt(b, a, n, re, mo);
    output(re);
    puts("");  
    return 0;
}