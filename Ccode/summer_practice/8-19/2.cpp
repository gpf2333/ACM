#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int a[maxn];
int main(){
    int n;
    scanf("%d", &n);
    if((n & 1) == 0){
        puts("NO"); return 0;
    }
    int cnt = 1;
    for(int i = 1; i <= n; ++i){
        if(i & 1){
            a[i] = cnt++, a[i + n] = cnt++; 
        }else{
            a[i + n] = cnt++, a[i] = cnt++;
        }
    }
    puts("YES");
    for(int i = 1; i <= (n << 1); ++i){
        printf("%d ", a[i]);
    }
    puts("");
    return 0;
}