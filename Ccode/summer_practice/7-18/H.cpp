#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
map<ull, int>mp;
vector<int>vec[maxn];
int main(){
    int n;
    ll x;
    while(~scanf("%d", &n)){
        mp.clear();
        for(int i = 0; i <= n; ++i){
            vec[i].clear();
        }
        int cnt = 0;
        mp[0] = cnt;
        vec[cnt++].push_back(0);
        ll tmp = 0;
        for(int i = 1; i <= n; ++i){
            scanf("%lld", &x);
            tmp ^= x;
            if(mp.count(tmp)){
                vec[mp[tmp]].push_back(i);
            }else{
                mp[tmp] = cnt++;
                vec[mp[tmp]].push_back(i);
            }
        }
        ll ans = 0;
        for(int i = 0; i < cnt; ++i){
            if(vec[i].size() <= 1) continue ;
            int len = vec[i].size();
            if(len & 1){
                if(len == 3){
                    ans = (ans + (vec[i][1] - vec[i][0] + 1) * 2LL % mod) % mod;
                    ans = (ans + (vec[i][2] - vec[i][1] + 1) * 2LL % mod) % mod;
                }else{
                    int up = len >> 1;
                    ans = (ans + (ll)(vec[i][1] - vec[i][0]) * (len - 1) % mod) % mod;
                    ll tt = 2LL * len - 4;
                    for(int j = 2; j <= up; ++j){
                        ans = (ans + (tt * (vec[i][j] - vec[i][j - 1])) % mod) % mod;
                        tt += 2;
                    }
                    tt = 2LL * len - 4;
                    for(int j = len - 2; j > up; --j){
                        ans = (ans + (tt * (vec[i][j] - vec[i][j - 1])) % mod) % mod;
                        tt += 2;
                    }
                    ans = (ans + (ll)(vec[i][len - 1] - vec[i][len - 2]) * (len - 1) % mod) % mod;
                }
            }else{
                if(len == 2){
                    ans = (ans + (vec[i][1] - vec[i][0])) % mod;
                }else{
                    int up = len >> 1;
                    ans = (ans + (ll)(vec[i][1] - vec[i][0]) * (len - 1) % mod) % mod;
                    ll tt = 2LL * len - 4;
                    for(int j = 2; j < up; ){
                        ans = (ans + (tt * (vec[i][j] - vec[i][j - 1])) % mod) % mod;
                        if(j++ != up) tt += 2;
                    }
                    tt += 1;
                    ans = (ans + tt * (vec[i][up] - vec[i][up - 1]) % mod) % mod;
                    tt = 2LL * len - 4;
                    for(int j = len - 2; j > up; ){
                        ans = (ans + (tt * (vec[i][j] - vec[i][j - 1])) % mod) % mod;
                        if(--j != up) tt += 2;
                    }
                    ans = (ans + (ll)(vec[i][len - 1] - vec[i][len - 2]) * (len - 1) % mod) % mod;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}