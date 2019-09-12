#include<bits/stdc++.h>
using namespace std;
int main(){
    int m;
    int kase = 0;
    int f[] = {0, 0, 0, 0, 1};
    while(~scanf("%d",&m)){
        if(m <= 4){
            printf("Case #%d: %d\n", ++kase, f[m]);
            continue ;
        }
        const double tmp = log2(10 * 1.0);
        const double up = (double)m;
        int k = floor(up / tmp);
        printf("Case #%d: %d\n", ++kase, k);
    }
}