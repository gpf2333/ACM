#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const double eps = 1e-6;
vector<ll>vec;
bool vis[505];
set<ll>s;
unordered_map<ll, int>mp;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n; 
    cin >> n;
    for(int i = 0; i < n; ++i){
        ll x; 
        cin >> x;
        ll tmp1 = pow(x, 0.5) + 0.5;
        ll tmp2 = pow(x, 1.0 / 3) + 0.5;
        ll tmp3 = pow(x, 0.25) + 0.5;
        if(tmp3 * tmp3 * tmp3 * tmp3 == x){
            mp[tmp3] += 4; 
            s.insert(tmp3);
            continue ;
        }else if(tmp2 * tmp2 * tmp2 == x){
            mp[tmp2] += 3; 
            s.insert(tmp2);
            continue ;
        }else if(tmp1 * tmp1 == x){
            mp[tmp1] += 2; 
            s.insert(tmp1);
            continue ;
        }else{
            vec.push_back(x);
        }
    }
    ll ans = 1, p = -1;
    sort(vec.begin(), vec.end());
    memset(vis, 0, sizeof(vis));
    for(int  i = 0; i < (int)vec.size(); ++i){
        if(vis[i]) continue ;
        int cnt = 0;
        p = -1;
        for(int j = 0; j < (int)vec.size(); ++j){
            if(vec[i] == vec[j]){
                ++cnt;
                vis[j] = 1; 
                continue ;
            }
            ll d = __gcd(vec[i], vec[j]);
            if(d != 1 && d != vec[i]){
                p = d; 
            }
        }
        for(auto v: s){
            if(vec[i] % v == 0){
                p = v; break ;
            }
        }
        if(p == -1){
            ans = ans * (1LL + cnt) % mod * (1LL + cnt) % mod;
        }else{
            mp[p] += cnt;
            mp[vec[i] / p] += cnt;
        }
    }
    for(auto v: mp){
        ans = (ans * (1 + v.second)) % mod;
    }
    cout << ans << endl;
    return 0;
}