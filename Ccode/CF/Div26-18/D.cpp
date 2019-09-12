#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int cnt[110];
int a[maxn];
int main(){
    int n, m;
    memset(cnt, 0, sizeof(cnt));
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; ++i){
        scanf("%d",&a[i]);
    }
    int sum = 0;
    for(int i = 0; i < n; ++i){
        int c = 0;
        sum += a[i];
        int ssum = sum;
        for(int t = 100; ssum > m && t >= 1;  --t){
            if(cnt[t]){
                if(ssum - t * cnt[t] >= m){
                    c += cnt[t];
                    ssum -= t * cnt[t];
                }else{
                    int tmp = (ssum - m) / t;
                    if(tmp * t < (ssum - m)){
                        ++tmp;
                    }
                    c += tmp;
                    ssum -= t * tmp;
                }   
            }
        }
        printf("%d%c",c, (i == n - 1)?'\n':' ');
        ++cnt[a[i]];
    }
    return 0;
}