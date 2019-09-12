#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

int check(const char c){
    if(c == 'a') return 0;
    if(c == 'v') return 1;
    if(c == 'i') return 2;
    if(c == 'n') return 3;
    return 4;
}

int main(){
    int n;
    char s[105];
    int cnt[5];
    while(~scanf("%d", &n)){
        scanf("%s", s);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; s[i]; ++i){
            int tmp = check(s[i]);
            if(tmp < 4) ++cnt[tmp];
        }
        if(!cnt[0] || !cnt[1] || !cnt[2] || !cnt[3]){
            puts("0/1");
            continue ;
        }
        ll tmp = 1;
        ll res = 1;
        for(int i = 0; i < 4; ++i){
            tmp *= cnt[i];
            res *= n;
        }
        ll d = gcd(tmp, res);
        tmp /= d, res /= d;
        printf("%lld/%lld\n", tmp, res);
    }
    return 0;
}