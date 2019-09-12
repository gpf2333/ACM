#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
const int mod = 998244353;
const int maxn = 1e7 + 5;
bool isprime[maxn]; 
int cntp, prime[maxn], phi[maxn];

int fast_pow(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

const int inv2 = fast_pow(2, mod - 2);
const int inv6 = fast_pow(6, mod - 2);

void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    cntp = 0;
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(!(i % prime[j])){
                phi[i * prime[j]] = phi[i] * prime[j];
                break ;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

template <class T>
void read(T &x) {
	static char ch;
    static bool neg;
	for(ch = neg = 0; ch<'0' || '9' < ch; neg|= ch =='-', ch = getchar());
	for(x = 0; '0'<=ch && ch <= '9'; (x*=10) += ch - '0', ch = getchar());
	x = neg? -x: x;
}

template <class T>
void output(T x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9){
        output(x / 10);
    }
    putchar(x % 10 + '0');
}

template<class T>
T gcd(T a, T b){
    return b == 0 ? a : gcd(b, a % b);
}

i128 getn(const i128 n){
    i128 l = 1, r = 1e7, ans;
    while(l <= r){
        i128 mid = (l + r) >> 1;
        if(mid * mid * mid <= n){
            ans = mid, l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return ans;
}

ll calc(int a, i128 L, i128 R){
    ll res = 0;
    for(int i = 1; (ll)i * i <= a; ++i){
        if(!(a % i)){
            ll tmp = ((R / i - L / i) % mod + mod) % mod;
            res = (res + tmp * phi[i] % mod) % mod;
            if((ll)i * i != a){
                tmp = ((R /(a / i) - L / (a / i)) % mod + mod) % mod;
                res = (res + tmp * phi[a / i] % mod) % mod;
            }
        }
    }
    return res;
}

inline ll f(int n){
    return (ll)n * (n + 1) % mod * inv2 % mod;
}

inline ll f2(int n){
    return (ll)n * (n + 1) % mod * (2LL * n % mod + 1) % mod * inv6 % mod;
}

ll cal(int n){
    ll res = 0;
    for(int i = 1; i <= n; ++i){
        ll tmp = (3 * i % mod * f2(n / i) % mod + 3 * f(n / i) % mod + (n / i)) % mod;
        tmp = tmp * phi[i] % mod;
        res = (res + tmp) % mod;
    }
    return res;
}

int main(){
    init();
    i128 n;
    int T;
    read(T);
    while(T--){
        read(n);
        int a = getn(n);
        int r = a - 1;
        i128 L = (i128)a * a * a - 1;
        i128 R = n;
        ll res = calc(a, L, R);
        res = (res + cal(r)) % mod;
        printf("%lld\n", res);
    }
    return 0;
}