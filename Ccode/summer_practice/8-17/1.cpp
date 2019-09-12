#include<bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
typedef long long ll;

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

bool excrt(ll r[], ll m[], ll n, ll &re, ll &mo){
    ll x, y, tmp;
    mo = m[0], re = r[0];
    for(int i = 1; i < n; ++i){
        ll d = exgcd(mo, m[i], x, y);
        if((r[i] - re) % d != 0 ) return 0;
        x = (i128)(r[i] - re) / d * (i128)x % (m[i] / d);
        re += x * mo;
        mo = mo / d * m[i];
        re %= mo;
    }
    re = (re + mo) % mo;
    return 1;
}


char s[64];
template<typename T>
void output(T x){
    if(x < 0){
        putchar('-');
    }
    if(x == 0){
        putchar('0');
    }
    int cnt = 0;
    while(x){
        s[cnt++] = x % 10 + '0';
        x /= 10;
    }
    for(int i = cnt - 1; i >= 0; --i){
        putchar(s[i]);
    }
}

ll a[105], b[105];
int main(){
    ll x, y;
    ll d = exgcd(10, 5, x, y);
    // cout << d << " " << x << " " << y << endl;
    // int n;
    // ll m;
    // scanf("%d%lld", &n, &m);
    // for(int i = 0; i < n; ++i){
    //     scanf("%lld%lld", &a[i], &b[i]);
    // }
    // ll re, mo;
    // if(excrt(b, a, n, re, mo)){
    //     if(re > m){
    //         puts("he was definitely lying");
    //     }else{
    //         output(re);
    //         puts("");
    //         //printf("%lld\n", re);
    //     }
    // }else{
    //     puts("he was definitely lying");
    // }
    return 0;
}