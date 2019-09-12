#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 10;
int a[maxn];
void init(){
    a[1] = 1;
    a[2] = a[3] = 2;
    for(int i = 4, index = 3, flag = a[3]; i < maxn; ++index){
        int len = a[index];
        for(int j = 1; j <= len; ++j){
            if(flag == 1){
                a[i] = 2;
            }else if(flag == 2){
                a[i] = 1;
            }
            if(j == len) flag = a[i];
            ++i;
        }
    }
}
int main(){
    init();
    int n, T;
    scanf("%d", &T);
    while(T--){
        scanf("%d",&n);
        printf("%d\n", a[n]);
    }
}