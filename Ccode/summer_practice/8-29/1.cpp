#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int T, n, m, cas = 0;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        double ans1, ans2;
        if(n == 1) ans1 = 1.0;
        else ans1 = 0.5;
        ans2 = (m + 1.0) / (2.0 * m);
        printf("Case #%d: %.6lf %.6lf\n", ++cas, ans1, ans2);
    }
    return 0;
}