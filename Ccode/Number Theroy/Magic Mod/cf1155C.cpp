#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
typedef long long ll;
ll ax[maxn], p[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> ax[i];
    }
    ll x = ax[1], nx = ax[2];
    ll d = nx - x;
    for(int i = 3; i <= n; ++i){
        nx = ax[i];
        d = __gcd(d, nx - x);
        x = nx;
    }
    bool ok = 0;
    int id;
    for(int i = 1; i <= m; ++i){
        cin >> p[i];
        if(ok) continue ;
        if(d % p[i]) continue ;
        id = i, ok = 1;
    }
    if(!ok){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
        cout << ax[1] << " " << id << endl;
    }
    return 0;
}