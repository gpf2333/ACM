#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int a[maxn];
int b[maxn];
void diedai(int n){
    for(int i = 1; i <= n; ++i){
        b[i] = a[i];
    }
    int tmp = b[1];
    a[1] = b[1];
    for(int i = 2; i <= n; ++i){
        tmp ^= b[i];
        a[i] = tmp;
    }
}

int cnt = 0;
void output(const int *a, const int n){
    printf("%d: ", cnt++);
    for(int i = 1; i <= n; ++i){
        printf("%d%c", a[i], (i == n) ? '\n' : ' ');
    }
}

int main(){
    int n = 100, m = 64;
    for(int i = 1; i <= n; ++i){
        a[i] = (i + 1);
    }
    output(a, n);
    for(int i = 1; i <= m; ++i){
        diedai(n);
        output(a, n);
    }
    return 0;
}