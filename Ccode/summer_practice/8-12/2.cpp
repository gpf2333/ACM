#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx = 10;

ll calc(int i, int j, int k, int l, int r, int kk, int n){
    ll res = 0, cnt = 0;
    if(!i) ++cnt;
    if(!j) ++cnt;
    if(!k) ++cnt;
    if(!l) ++cnt;
    if(!r) ++cnt;
    if(kk == n - cnt){
        
    }
}

int main(){
    ios::sync_with_stdio(NULL);
    cin.tie(NULL);
    int T;
    cin >> T;
    ll n, m, k;
    while(T--){
        cin >> n >> m >> k;
        ll minn = 2e18;
        for(int i = 0; i <= mx; ++i){
            for(int j = 0; j <= mx; ++j){
                for(int k = 0; k <= mx; ++k){
                    for(int l = 0; l <= mx; ++l){
                        for(int r = 0; r <= mx; ++r){
                            if(i + j + k + l + r == m){
                                // cout << i << " " << j << " " << k << " " << l << " " << r << endl;
                            }
                        }
                    }
                }
            }
        }
        ll ans;
        if(n == k){
            ans = (m + 1) * k;
        }else{
            ans = (m / k + 1) * (k + 1);
        } 
        printf("%lld\n", ans);
    }
    return 0;
}