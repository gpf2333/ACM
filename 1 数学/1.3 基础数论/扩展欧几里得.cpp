

typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    ll d = a;
    if (b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

// ---
// 用法1： 求解线性方程 ax + by = c
// 引用返回通解: $X = x + k * dx, Y = y – k * dy$\\
// 引用返回的x是最小非负整数解，方程无解函数返回0
// 特别注意传入参数的正负性！！！
// 
// ---
#define Mod(a, b) (((a) % (b) + (b)) % (b))
bool solve(ll a, ll b, ll c, ll& x, ll& y, ll& dx, ll& dy)
{
    if (a == 0 && b == 0) return 0;
    //根据题目判断是否需要特判a = 0 && b != 0  or a != 0 && b == 0
    ll x0, y0;
    ll d = exgcd(a, b, x0, y0);
    if (c % d != 0) return 0;
    dx = b / d, dy = a / d; //
    x = Mod(x0 * c / d, dx);
    y = (c - a * x) / b;
    //  y = Mod(y0 * c / d, dy); x = (c - b * y) / a;
    return 1;
}

/*
---
扩展：
求解线性同余方程组
求解逆元
---
*/
ll get_inv(ll a,ll mod){
    ll x, y;
    ll d = exgcd(a, mod, x, y);
    if(d != 1) return -1; //逆元不存在
    return (x % mod + mod) % mod; //求解最小正逆元
}
