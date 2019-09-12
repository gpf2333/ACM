// #include<bits/stdc++.h>
// using namespace std;
// const int maxn = 1e3 + 100;
// struct Node{
//     int val, id;
// }a[maxn];
// bool cmp(const Node &a, const Node &b){
//     if(a.val == b.val) return a.id < b.id;
//     return a.val < b.val;
// }

// long long b[maxn];
// int main(){
//     int n;
//     while(~scanf("%d",&n)){
//         for(int i = 0; i < n; ++i){
//             scanf("%d",&a[i].val);
//             a[i].id = i;
//         }
//         sort(a, a + n, cmp);
//         double ans = 0;
//         for(int i = 0; i < n; ++i){
//             printf("%d%c", a[i].id + 1, (i == n - 1) ? '\n' : ' ');
//             if(i == 0) b[i] = 0;
//             else b[i] = b[i - 1] + a[i - 1].val;
//             ans += b[i];
//         }
//         printf("%.2lf\n", ans / n);
//     }
//     return 0;
// // }

#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
int a[maxn];
int main(){
    int up, n;
    scanf("%d%d",&up,&n);
    for(int i = 0; i < n; ++i){
        scanf("%d",&a[i]);
    }
    sort(a, a + n);
    int ans = 0, l = 0, r = n - 1;
    while(l <= r){
        if(a[l] + a[r] <= up){
            ++l, --r;
            ++ans;
        }else{
            ++ans;
            --r;
        }
    }
    printf("%d\n", ans);
    return 0;
}