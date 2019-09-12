#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
const int INF = 0x3f3f3f3f;
int a[maxn], dp[maxn];
int LIS(int a[], int dp[], int n){
    for(int i = 1; i <= n; ++i) dp[i] = INF;
    dp[0] = a[0];
    int pos = 0;
    for(int i = 1; i < n; ++i){
        if(a[i] > dp[pos]){
            dp[++pos] = a[i];
        }else{
            *lower_bound(dp, dp + pos + 1, a[i]) = a[i];
        }
    }
    return pos + 1;
}



//ForwardIter lower_bound(ForwardIter first, ForwardIter last,const _Tp& val)算法返回一个非递减序列[first, last)中的第一个大于等于值val的位置。
//ForwardIter upper_bound(ForwardIter first, ForwardIter last, const _Tp& val)算法返回一个非递减序列[first, last)中第一个大于val的位置。

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string s;
    while(getline(cin, s)){
        stringstream ss(s);
        int x;
        n = 0;
        while(ss >> x){
            a[n++] = x;
        }
        int cnt = LIS(a, dp, n);
        int pos = 0;
        for(int i = 1; i < n; ++i) dp[i] = INF;
        dp[0] = a[0];
        for(int i = 1; i < n; ++i){
            if(dp[pos] >= a[i]){
                dp[++pos] = a[i];
            }else{
                *upper_bound(dp, dp + pos + 1, a[i], greater<int>()) = a[i];
            }
        }
        int sum = pos + 1;
        printf("%d\n%d\n", sum, cnt);
    }
    return 0;
}