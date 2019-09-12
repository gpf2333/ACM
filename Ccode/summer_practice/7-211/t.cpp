#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
int a[maxn];
int main(){
    int n;
    while(~scanf("%d",&n)){
        string x;
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            cin >> x;
            int j = 0;
            for(j = 0; j < x.size(); ++j){
                if(x[j] == '.') break ;
            }
            if(x[j + 3] < '5'){
                cnt -= x[j + 3] - '0';
            }else{
                cnt += (10 - x[j + 3] + '0');
            }
        }
        double ans = (double)cnt / 1000.0;
        printf("%.3lf\n", ans);
    }
    return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 1000 + 5;
// int a[maxn];
// int main(){
//     int n;
//     while(~scanf("%d",&n)){
//         double x;
//         double ans = 0.000;
//         for(int i = 0; i < n; ++i){
//             cin >> x;
//             x = x - (int)x;
//             x *= 1000;
//             //if(x%100>)
//             ans += x - round(x);
//         }
//         printf("%.3lf\n", -1.0 * ans / 100);
//     }
//     return 0;
// }