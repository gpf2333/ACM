#include <bits/stdc++.h>
using namespace std;
#define maxn 300005
#define MOD 998244353
#define mod MOD
#define G 3
typedef long long ll;
int rev[maxn];
long long C[maxn];

inline ll Pow(ll a, ll k) {
    ll base = 1;
    while (k) {
        if (k & 1) base = (base * a) % MOD;
        a = (a * a) % MOD;
        k >>= 1;
    }
    return base % MOD;
}

void NTT(long long *a, int len, int opt) {
    for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int i = 1; i < len; i <<= 1) {
        long long wn = Pow(G, (opt * ((MOD - 1) / (i << 1)) + MOD - 1) % (MOD - 1));
        int step = i << 1;
        for (int j = 0; j < len; j += step) {
            long long w = 1;
            for (int k = 0; k < i; ++k, w = (1ll * w * wn) % MOD) {
                long long x = a[j + k];
                long long y = 1ll * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD;
                a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if (opt == -1) {
        long long r = Pow(len, MOD - 2);
        for (int i = 0; i < len; i++)
            a[i] = 1ll * a[i] * r % MOD;
    }
}

void solve(ll A[],ll B[],int n, int m) {
    int x, l = 0 ,len = 1;
    while (len <= n + m) len <<= 1, ++l;
    for (int i = 0; i < len; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; ++i) {
        C[i] = (ll) (A[i] * B[i]) % MOD;
        A[i] = B[i] = 0;
    }
    NTT(C, len, -1);
}
void read(ll &x) {
    static char ch;static bool neg;
    for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
    for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
    x=neg?-x:x;
}
int n,cnt[4];
ll a[maxn],c[maxn];
ll fac[1000005],inv[1000005];
ll pow_mod(ll m,ll n)
{
    ll res=1;
    while (n)
    {
        if(n&1)res=res*m%mod;
        m=m*m%mod;
        n>>=1;
    }
    return res;
}
void init()
{
    inv[0]=fac[0]=1;
    for(int i=1;i<=1000000;i++)fac[i]=fac[i-1]*i%mod;
    inv[1000000]=pow_mod(fac[1000000],mod-2);
    for(int i=999999;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
ll Comb(int n,int m)
{
    return n<m?0:fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int main()
{
    init();//组合数预处理
    int T;
    cin>>T;
    while (T--)
    {
        memset(cnt,0, sizeof(cnt));
        ll m,op;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            read(a[i]);
        }
        for(int i=1;i<=m;i++)
        {
            read(op);
            ++cnt[op];
        }
    
        for(int i=1;i<=3;i++)
        {
            memset(c,0, sizeof(c));
            for(int j=0;j*i<n;j++)
            {
                c[j*i]=Comb(cnt[i]-1+j,j);
            }
            if(cnt[i]==0)c[0]=1;//特殊处理
            solve(a+1,c,n,n);
            for(int i=0;i<n;i++)a[i+1]=C[i];
        }
        ll ans=0;
        for(int i=1;i<=n;i++)ans=ans^(1ll*i*a[i]);
        cout<<ans<<endl;
    }
    return 0;
}