// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int maxn = 3e5 + 10;
// const int mod = 1e9 + 7;
// const int mod1 = 1004535809;
// map<pair<int, int>, int>mp;

// int fast_pow(int a, int b, const int mod) {
//     int res = 1;
//     while(b > 0) {
//         if(b & 1) res = (ll)res * a % mod;
//         a = (ll) a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }

// int main() {
//     mp.clear();
//     int n, x;
//     scanf("%d",&n);
//     int fir = 0, sec = 0;
//     ++mp[make_pair(fir, sec)];
//     for(int i = 1; i <= n; ++i) {
//         scanf("%d", &x);
//         fir ^= fast_pow(2, x, mod), 
//         sec ^= fast_pow(2, x, mod1);
//         ++mp[make_pair(fir, sec)];
//     }
//     ll ans = 0;
//     for(auto it : mp) {
//         ans += ((ll)it.second * (it.second - 1) / 2);
//     }
//     printf("%lld\n", ans);
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
mt19937_64 rnd;

const int maxn = 3e5 + 10;
unordered_map<int, ull>ump;
map<ull, int>mp;

ull get_hash(const int x){
    if(ump.count(x)) return ump[x];
    else return ump[x] = rnd();
}

int main(){
    int n, x;
    scanf("%d", &n);
    ull tmp = 0;
    ++mp[tmp];
    for(int i = 0; i < n; ++i){
        scanf("%d", &x);
        tmp ^= get_hash(x);
        ++mp[tmp];
    }
    ll ans = 0;
    for(auto it: mp){
        ans += (ll)it.second * (it.second - 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}