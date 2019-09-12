#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100 + 50;
int main(){
    int n, m;
    int a[maxn];
    int b[maxn];
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; ++i){
        scanf("%d",&a[i]);
    }
    for(int i = 1; i <= n; ++i){
        if(i == 1){
            cout << 0;
            continue ;
        }
        ll sum = a[i - 1];
        for(int j = 0; j < i - 1; ++j){
            b[j] = a[j];
            sum += b[j];
        }
        sort(b, b + i - 1);
        int cnt = 0;
        for(int j = i - 2; j >= 0 && sum  > m; --j){
            sum -= b[j];
            ++cnt;
        }
        printf(" %d", cnt);
    }
    puts("");
    return 0;
}