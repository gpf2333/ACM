// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 1e4 + 5;
// struct Node{
//     int p, t;
// }a[maxn];
// int num[maxn], dp[maxn];

// bool cmp(const Node &a, const Node &b){
//     return a.p > b.p;
// }

// int main(){
//     int n, k;
//     memset(dp, 0, sizeof(dp));
//     memset(num, 0, sizeof(num));
//     scanf("%d%d",&n,&k);
//     for(int i = 0; i < k; ++i){
//         scanf("%d%d", &a[i].p, &a[i].t);
//         ++num[a[i].p];
//     }
//     sort(a, a + k, cmp);
//     for(int i = n, cnt = 0; i; --i){
//         if(!num[i]){
//             dp[i] = dp[i + 1] + 1;
//         }else{
//             for(int j = 1; j <= num[i]; ++j){
//                 if(dp[i + a[cnt].t] > dp[i]){
//                     dp[i] = dp[i + a[cnt].t];
//                 }
//                 ++cnt;
//             }
//         }
//     }
//     printf("%d\n", dp[1]);
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
char s[maxn];
int main(){
    int n ,sum1[maxn], sum2[maxn];
    memset(sum1, 0, sizeof(sum1));
    memset(sum2, 0, sizeof(sum2));
    scanf("%d%s",&n, s);
    for(int i = 0; i < n; ++i){
        if(s[i] == '0'){
            if(i){
                sum1[i] = sum1[i - 1] + 1;
                sum2[i] = sum2[i - 1];
            }else{
                sum1[i] = 1;
                sum2[i] = 0;
            }
        }
        else{
            if(i){
                sum1[i] = sum1[i - 1];
                sum2[i] = sum2[i - 1] + 1;
            }else{
                sum1[i] = 0;
                sum2[i] = 1;
            }
        }
    }
    if(sum1[n - 1] != sum2[n - 1]){
        printf("%d\n%s\n", 1, s);
        return 0;
    }
    else{
        int pos = -1;
        for(int i = 0; i < n; ++i){
            if(sum1[i] == sum2[i]) continue ;
            else{
                pos = i;
                break ;
            }
        }
        printf("2\n");
        for(int i = 0; i <= pos; ++i){
            putchar(s[i]);
        }
        putchar(' ');
        for(int i = pos + 1; i < n; ++i){
            putchar(s[i]);
        }
        putchar('\n');
    }
}
