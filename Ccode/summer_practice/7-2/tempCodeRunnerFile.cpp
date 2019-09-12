#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int a[maxn], b[maxn];

void output(const int *a, const int n){
    for(int i = 1; i <= n; ++i){
        printf("%d%c", a[i], (i == n) ? '\n' : ' ');
    }
}

void calc(int *a, int *b, int n){
    b[1] = a[1];
    for(int i = 2; i <= n; ++i){
        b[i] = a[i] ^ b[i - 1];
    }
    for(int i = 1; i <= n; ++i){
        a[i] = b[i];
    }
}

int main(){
    int T, n, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
        }
        int t = m % 32;
        for(int i = 1; i <= t; ++i){
            calc(a, b, n);
        }
        output(b, n);
    }
    return 0;
}