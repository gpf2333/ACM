#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y){
    ll d = a;
    if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
}

int main(){
    int T, cas = 0;
    scanf("%d", &T);
    while(T--){
        ll x, y;
        ll x1, x2, y1, y2;
        scanf("%lld%lld", &x, &y);
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        printf("Case #%d:\n", ++cas);
        double ansx, ansy;
        bool ok = 1;
        if(x1 == x2 && y1 == y2){
            ansx = x1, ansy = y1;
        }else if(x1 == x2 && y1 != y2){
            if(y1 > y2) swap(y1, y2);
            double t = (2 * y - y1 - y2);
            ansx = t / 2 + x1;
            ansy = t / 2 + y1;
        }else if(x1 != x2 && y1 == y2){
            if(x1 > x2) swap(x1, x2);
            double t = (2 * x - x1 - x2);
            ansx = t / 2 + x1;
            ansy = t / 2 + y1;
        }else{
            x *= 2, y *= 2, x1 *= 2, x2 *= 2, y1 *= 2, y2 *= 2;
            ll z = __gcd(x, y);
            ll minx, miny;
            ll c = (2 * y - y1 - y2 - 2 * x + x1 + x2) / 2;
            if(c % z!=0){
                ok = 0;
            }
            else{
                ll xx = x /d, yy = y / d;
                c /= d;
                exgcd(xx, yy, minx, miny);
                minx *= c;
                minx = (minx % yy + yy) % yy;
                ll t = minx * x + (2 * x - x1 - x2) / 2;
                ansx = (x1 + t) % (2 * x);
                ansy = (y1 + t) % (2 * y);
                if(ansx > x) ansx = 2 * x - ansx;
                if(ansy > y) ansy= 2 * y - ansy;
                ansx /= 2, ansy /= 2;
            }
        }
        if(ok) printf("%.1lf %.1lf\n", ansx, ansy);    
        else printf("Collision will not happen.\n");
    }
    return 0;
}