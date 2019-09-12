#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200000000 + 5;
char b[maxn];
char c[30];

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
    int res = n;
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            res -= res / i;
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1) res -= res / n;
    return res;
}

int getmod(const char *s, const int mod){
    int res = 0;
    for(int i = 0; s[i]; ++i){
        res = ((ll)res * 10LL + (s[i] - '0')) % mod;
    }
    return res;
}

int main(){
    int a, m;
    while(~scanf("%d%d%s", &a, &m, b)){
        int phi = getphi(m);
        int cnt = 0, tmp = phi;
        while(tmp){
            c[cnt++] = tmp % 10 + '0';
            tmp /= 10;
        }
        c[cnt] = '\0';
        reverse(c, c + cnt);
        int len = strlen(b), flag;
        if(len > cnt){
            flag = 1;
        }else if(len < cnt){
            flag = -1;
        }else{
            flag = strcmp(b, c);
        }
        int ans;
        if(flag >= 0){
            ans = qpow(a, getmod(b, phi) + phi, m);
        }else{
            tmp = 0;
            for(int i = 0; b[i]; ++i){
                tmp = tmp * 10 + (b[i] - '0');
            }
            ans = qpow(a, tmp, m);
        }
        printf("%d\n", ans);
    }
    return 0;
}