#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-10;
double r,c,h;
struct point{
    double x,y;
}p,q;
double dis(point a, point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int judge(double b){
    double a = sqrt(b*b+c*c);
    double A = a*a-b*b;
    double B = -2*h*a*a;
    double C = a*a*h*h+b*b*r*r-a*a*b*b;
    double delta = B*B - 4*A*C;
    int cnt = 0;
    if(delta>=0){
        double y1=(-B+sqrt(delta))/(2*A);
        double y2=(-B-sqrt(delta))/(2*A);
        if(y1<=r&&y1>=-r)
            cnt++;
        if(y2<=r&&y2>=-r)
            cnt++;
    }
    return cnt;
}
double binarysearch(double l,double r){
    double mid;
    while(r-l>eps){
        mid = (l+r)/2;
        int flag = judge(mid);
        if(flag>1)
            r=mid;
        else
            l=mid;
        if(flag==1)
        {
            break;
        }
    }
    return mid;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lf%lf%lf%lf%lf",&r,&p.x,&p.y,&q.x,&q.y);
        c = dis(p,q)/2;
        h = sqrt(p.x*p.x+p.y*p.y-c*c);
        double b = binarysearch(0,r-h);
        double a = sqrt(b*b+c*c);
        printf("%.7lf\n",2*a);
    }
}
