#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
using namespace std;
const int maxn = 1e6 + 5;
const int INF = 0x3f3f3f3f;
double a1,b1,a2,b2,c1,c2;

bool IsInTriangle(double x, double y, double ax, double ay, double bx, double by, double cx, double cy)
{
    return  (bx - ax) * (y - ay) > (by - ay) * (x - ax) &&
            (cx - bx) * (y - by) > (cy - by) * (x - bx) &&
            (ax - cx) * (y - cy) > (ay - cy) * (x - cx) ? false : true;
}

inline double getarea(double a1, double a2, double b1, double b2, double c1, double c2){
    return ((a1 * b2 - a2 * b1) + (a2 * c2 - c1 * b2) + (c1 * b1 - a1 * c2)) / 2;
}

map<pair<double, double>, int>mp;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>a1>>b1>>a2>>b2>>c1>>c2){
        double S=((a1*b2-a2*b1)+(a2*c2-c1*b2)+(c1*b1-a1*c2))/2;
        if(S == 0) cout<<0<<endl;
        else{
            mt19937 Rand(time(0));
            double tmp = 0.0;
            mp.clear();
            mp[make_pair(a1, a2)] = 1;
            mp[make_pair(b1, b2)] = 1;
            mp[make_pair(c1, c2)] = 1;
            int n = 100000;
            while(n--){
                double i = Rand()% 1000000 * 1.0 / 1000000;
                double j = Rand()% 1000000 * 1.0 / 1000000;
                if(IsInTriangle((double)i, (double)j, a1, a2, b1, b2, c1, c2)){
                    double s1 = getarea(i, j, a1, a2, b1, b2);
                    double s2 = getarea(i, j, a1, a2, c1, c2);
                    double s3 = getarea(i, j, b1, b2, c1, c2);
                    tmp += max(s1, max(s2, s3)) / S;
                }
            }
            unsigned long long  ans = tmp * 36;
            cout << ans << endl;
        }
    }
}