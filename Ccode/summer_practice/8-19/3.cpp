#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 128 + 10;
const ll INF = 1e12;
ll a[maxn];
ll d[maxn][maxn], dis[maxn][maxn];
int cnt[70];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, tot = 0;
    cin >> n;
    for(int i = 0; i < n; ++i){
        ll x;
        cin >> x;
        if(x && tot < 128){
            a[tot++] = x;
        }
        if(x){
            for(int j = 0; j < 64; ++j){
                if((x >> j) & 1){
                    ++cnt[j];
                }
            }
        }
    }
    for(int i = 0; i < 64; ++i){
        if(cnt[i] >= 3){
            cout << 3 << endl;
            return 0;
        }
    }
    for(int i = 0; i < tot; ++i){
        for(int j = i + 1; j < tot; ++j){
            if(a[i] & a[j]){
                d[i][j] = dis[i][j] = 1;
                d[j][i] = dis[j][i] = 1;
            }else{
                d[i][j] = dis[i][j] = INF;
                d[j][i] = dis[j][i] = INF;
            }
        }
    }
    ll ans = INF;
    for(int k = 0; k < tot; ++k){
        for(int i = 0; i < k; ++i){
            for(int j = i + 1; j < k; ++j){
                ans = min(ans, d[i][k] + d[k][j] + dis[i][j]);
            }
        }
        for(int i = 0; i < tot; ++i){
            for(int j = 0; j < tot; ++j){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); 
            }
        }
    }
    if(ans == INF) ans = -1;
    cout << ans << endl;
    return 0;
}