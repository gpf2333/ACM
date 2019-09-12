/*
题意：n*m的矩形内有k个点，四周有围墙围起来。从(0,0)45度发射小球，
速度为2–√每次遇到墙都正常反弹，直到射到顶点被吸收。问每个点第一次被经过的时刻。
把矩形对称展开，最后小球在横纵坐标均为maxx=mn/gcd(m,n)maxx=mn/gcd(m,n)处被吸收。 
原坐标为(x,y)(x,y)的小球经过轴对称展开，其坐标为(2kn±x,2sm±y),k,s为整数(2kn±x,2sm±y),k,s为整数.要使得在吸收前经过点，则坐标必须在线段(0, 0)到(maxx, mxx)之间。 
即要解方程2kn±x=2sm±y2kn±x=2sm±y，求为正最小的2kn±x2kn±x。利用扩展欧几里得解方程。
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll exgcd(ll a, ll b, ll &x, ll &y){
   ll d = a;
   if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
   else x = 1, y = 0;
   return d; 
}

// x = x + k * dx, y = y - k * dy
inline int Mod(ll a, ll b){
    return (a % b + b) % b;
}
bool solve(ll a, ll b, ll c, ll &x, ll &y, ll &dx, ll &dy){
    if(!a && !b) return 0;
    if(!a && b){
        if(c % b) return 0;
        x = 0, dx = 0;
        y = c / b, dy = 0;
        return 1;
    }
    if(a && !b){
        if(c % a) return 0;
        x = c / a, dx = 0;
        y = 0, dy = 0;
        return 1;
    }
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if(c % d) return 0;
    dx = b / d, dy = a / d;
    x = Mod(x0 * c / d, dx);
    y = (c - a * x) / b;
    return 1;
}

ll n, m, up;
ll calc(ll x1, ll y1){
    ll x, y, dx, dy;
    if(!solve(2 * n, 2 * m , y1 - x1, x, y, dx, dy)) return INF;
    ll tmp = 2 * n * x + x1;
    if(tmp < 0 || tmp > up) return INF;
    return tmp; 
}

ll work(ll x, ll y){
    ll ans = INF;
    ans = min(ans, calc(x, y));
    ans = min(ans, calc(x, -y));
    ans = min(ans, calc(-x, y));
    ans = min(ans, calc(-x, -y));
    return ans == INF ? -1 : ans;
}   

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int k;
    cin >> n >> m >> k;
    up = n / __gcd(n, m) * m;
    while(k--){
        int x, y;
        cin >> x >> y;
        cout << work(x, y) << endl;
    }
    return 0;
}