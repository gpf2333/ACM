// #pragma comment(linker, /STACK:102400000,102400000)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace IO{
    #define maxn 100000
    bool IOerror = 0;
    inline char nc(){
        static char buf[maxn], *p1 = buf + maxn, *pend = buf + maxn;
        if(p1 == pend){
            p1 = buf;
            pend = buf + fread(buf, 1, maxn, stdin);
            if(pend == p1){
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch){
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x){
        char ch;
        while(blank(ch = nc())) ;
        if(IOerror) return ;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; ){
            x = x * 10 + ch - '0';
        }
    }
    #undef maxn
};
using namespace IO;

const int mod = 1e9 + 7;
const int maxn = 1e6 + 50;
struct Node{
    int id, l, r;
    bool operator < (const Node &b) const {
        if(l == b.l) return r > b.r;
        return l < b.l;
    }
}a[maxn];

int fac[maxn], inv[maxn], invf[maxn];
void init(){
    fac[0] = fac[1] = inv[0] = inv[1] = invf[0] = invf[1] = 1;
    for(int i = 2; i < maxn; ++i){
        fac[i] = (ll)fac[i - 1] * i % mod;
        inv[i] = (ll)(mod - mod / i) * (ll)inv[mod % i] % mod;
        invf[i] = (ll)invf[i - 1] * (ll)inv[i] % mod;
    }
}

inline ll C(int n, int m){
    if(m > n) return 0;
    return ((ll)fac[n] * invf[n - m] % mod) * (ll)invf[m] % mod;
}

ll dfs(int l, int r, int &cnt, bool &flag){
    if(!flag) return 0;
    if(l > r) return 1;
    if(a[cnt].l != l || a[cnt].r != r) {
        flag = 0;
        return 0;
    }
    int id = a[cnt].id, curl = a[cnt].l, curr = a[cnt].r;
    ++cnt;
    return (C(curr - curl, id - curl) * dfs(curl, id - 1, cnt, flag) % mod * dfs(id + 1, curr, cnt, flag)) % mod;
}

int main(){
    init();
    int n, kase = 0;
    while(IO::read(n), !IO::IOerror){
        for(int i = 1; i <= n; ++i){
            IO::read(a[i].l);
            a[i].id = i;
        }
        for(int i = 1; i <= n; ++i){
            IO::read(a[i].r);
        }
        sort(a + 1, a + n + 1);
        bool flag = true;
        int cnt = 1;
        printf("Case #%d: %lld\n", ++kase, dfs(1, n, cnt, flag));
    }
    return 0;
}