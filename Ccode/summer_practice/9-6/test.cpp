// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef pair<double, double> pdd;
// const int MAXN = 1e6;
// const int mod = 1e9 + 7;
// ll qpow(ll a, ll b){
//     ll res = 1;
//     a %= mod;
//     while(b > 0){
//         if(b & 1) res = res * a % mod;
//         a = a * a % mod;
//         b >>= 1;
//     }
//     return res;
// }
// int main()
// {
//     int T;
//     cin >> T;
//     while(T--){
//         ll n;
//         cin >> n;
//         ll ans = n % mod * qpow(qpow(2, n - 1) % mod, mod - 2) % mod;
//         cout << ans % mod << endl;
//     }
//     return 0;
// }
// // vector<pdd>vec;
// // int main(){
// //     ios::sync_with_stdio(0);
// //     cin.tie(0), cout.tie(0);
// //     int T;
// //     cin >> T;
// //     while(T--){
// //         ll n;
// //         cin >> n;
// //         mt19937 rnd(time(0));
// //         int up = 1e4, sum = up;
// //         int cnt = 0;
// //         while(up--){
// //             vec.clear();
// //             for(int i = 0; i < n; ++i){
// //                 int t = rnd() % 2;
// //                 double x = rnd() % MAXN / (double) MAXN;
// //                 if(t & 1) x = -x;
// //                 t = rnd() % 2;
// //                 double y = 1 - x * x;
// //                 if(t & 1) y = -y;
// //                 vec.emplace_back(x, y);
// //             }
// //             double maxx = -MAXN, minn = MAXN;
// //             for(auto v: vec){
// //                 double x = v.first, y = v.second;
// //                 double tmp = atan2(y, x) * 180 / acos(-1.0);
// //                 maxx = max(maxx, tmp);
// //                 minn = min(minn, tmp);
// //             }
// //             //cout << maxx << " " << minn << endl;
// //             if(maxx - minn <= 180 || ){
// //                 cnt++;
// //             }


// //         }
// //         cout << cnt << " " << sum << endl;
// //         cout << 1.0 * cnt / sum << endl;
// //     }
// //     return 0;
// // }

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll INF = 1e18 + 10;
map<ll, bool>mp;
ll a[100000];
void init(){
    a[0] = 0;
    mp[0] = 1;
    ll cnt = 1;
    while(1){
        if(4.00 * a[cnt] > INF) break ;
        a[2 * cnt] = 4LL * a[cnt];
        mp[a[2 * cnt]] = 1;
        if(4.00 * a[cnt] + 2 > INF) break ;
        a[2 * cnt + 1] = 4LL * a[cnt] + 2;
        mp[a[2 * cnt + 1]] = 1;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    init();
    int T;
    cin >> T;
    while(T--){
        ll n;
        cin >> n;
        if(mp.count(n)){
            cout << "Cuber QQ Win" << endl;
        }else{
            cout << "Little Fang Win" << endl;
        }
    }
    return 0;
}