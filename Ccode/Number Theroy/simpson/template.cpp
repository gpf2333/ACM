#include<bits/stdc++.h>
using namespace std;

double a,b;  //全局变量,依据题目而定
const double eps = 1e-5;  //eps精度具体参考题目精度要求
double f(double x){  //f函数具体看题目给的表达式
    return b * sqrt(1.0 - x * x / (a * a));
}
//辛普森模板
double simpson(double a, double b){
    double c = (a + b) / 2.0;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6.0;
}
double intergral(double l, double r, double Eps){
    double mid = (l + r) / 2.0;
    double sl = simpson(l,mid), sr = simpson(mid, r), sm = simpson(l, r);
    if(fabs(sl + sr - sm) <= 15 * Eps){
        return sl + sr + (sl + sr - sm) / 15.0;
    }
    return intergral(l, mid, Eps / 2.0) + intergral(mid, r, Eps / 2.0);
}

int main(){
    int T;
    cin >> T;
    while(T--){
        double L, R;
        cin >> a >> b >> L >> R;
        printf("%.3lf\n", 2.0 * intergral(L,R,eps));
    }
    return 0;
}
