#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a, ll b, ll & x, ll &y){
    ll d = a;
    if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}
int Mod(ll a, ll b){
    return (a % b + b) % b;
}
bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy){
    if(!a && !b) return 0;
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if(c % d != 0) return 0;
    dx = b / d, dy = a / d;
    x = Mod(c / d * x0, dx);
    y = (c - a * x) / b;
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, a, b;
    cin >> n >> a >> b;
    ll x, y, dx, dy;
    if(!solve(a, b, n, x, y, dx, dy)){
        cout << "NO" << endl;
    }else{
        if(y >= 0){
            cout << "YES" << endl;
            cout << x << " " << y << endl;
        }else{
            cout << "NO" << endl;
        }
    }
}