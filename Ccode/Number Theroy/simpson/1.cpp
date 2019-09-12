#include<bits/stdc++.h>
using namespace std;

double a,b;
const double eps = 1e-12;  
double f(double x){
    return pow(x, a / x - x);
}
double simpson(double a, double b){
    double c = (a + b) / 2.0;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6.0;
}
double intergral(double l, double r, double Eps){
    double mid = (l + r) / 2.0;
    double sl = simpson(l,mid), sr = simpson(mid, r);
    if(fabs(sl + sr - Eps) <= 15 * eps){
        return sl + sr + (sl + sr - Eps) / 15.0;
    }
    return intergral(l, mid, sl) + intergral(mid, r, sr);
}

int main(){
    int T;
    scanf("%lf", &a);
    if(a < 0){
        puts("orz"); return 0;
    }
    printf("%.5lf\n", intergral(eps, 20, simpson(eps, 20)));
    return 0;
}