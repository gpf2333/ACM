#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
using namespace std;
const int maxn = 1e5+5;
const int INF = 0x3f3f3f3f;
const int mod = 1e8;
double a1,a2,b1,b2,c1,c2;
double S;

struct Point{
    double x;
    double y;
    Point(double a=0.0, double b=0.0) :x(a), y(b){ }
}A,B,C,T;

double cross(const Point &a, const Point &b, const Point &p)
{
    return (b.x - a.x)*(p.y - a.y) - (b.y - a.y)*(p.x - a.x);
}

bool toLeft(const Point &a, const Point &b, const Point &p)
{
    return cross(a, b, p) > 0;
}

inline bool inTriangle(const Point &p, const Point &a, const Point &b, const Point &c)
{
    bool res = toLeft(a, b, p);
    if (res != toLeft(b, c, p))
        return false;
    if (res != toLeft(c, a, p))
        return false;
    if (cross(a, b, c) == 0)
        return false;
    return true;
}

inline double getSS(double x1, double y1, double x2, double y2, double x3, double y3){
    double a = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    double b = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
    double c = sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
    double p = (a + b + c)/2;
    double s = sqrt(p*(p-a)*(p-b)*(p-c));
    return s;
}

int main()
{
    while(cin>>a1>>a2>>b1>>b2>>c1>>c2){
        A.x=a1;A.y=a2;B.x=b1;B.y=b2;C.x=c1;C.y=c2;
        S = getSS(a1,a2,b1,b2,c1,c2);
        if(S == 0) cout<<0<<endl;
        else{
            double tmp = 0.0;
            mt19937 Rand(time(0));
            int n = 1e6;
            double mx = (max(A.x, max(B.x, C.x)));
            double my = (max(A.y, max(B.y, C.y)));
            int m = n;
            int cnt = 0;
            while(m--){
                T.x = Rand()% mod * mx / mod;
                T.y = Rand()% mod * my / mod;
                if(inTriangle(T, A, B, C)){
                    double s1 = getSS(T.x, T.y, a1, a2, b1, b2);
                    double s2 = getSS(T.x, T.y, a1, a2, c1, c2);
                    double s3 = getSS(T.x, T.y, b1, b2, c1, c2);
                    tmp += max(s1, max(s2, s3));
                    ++cnt;
                }
            }
            cout << S << endl;
            double ans = tmp / (double)cnt * 36;
            cout << ans << endl;
            cout << ans / S << endl;
            cout << (long long)S * 22 << endl;
        }
    }
}
