#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y){
    ll d = a;
    if(b) d = exgcd(b, a % b, y , x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}
inline ll Mod(ll a, ll b){
    return (a % b + b) % b;
}
bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy){
    if(a == 0 && b == 0) return 0;
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if(c % d) return 0;
    dx = abs(b / d), dy = abs(a / d);
    x = Mod(x0 * c / d, dx);
    y = (c - a * x) / b;
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll x, y, dx, dy;
    if(!solve(a, -c, d - b, x, y, dx, dy)){
        cout << -1 << endl;
    }else{
        while(x < 0 || y < 0){
            x += dx;
            y += dy;
        }
        cout << b + a * x << endl;
    }
    return 0;
}