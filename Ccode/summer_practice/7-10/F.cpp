#include<bits/stdc++.h>
using namespace std;

inline void update(int x, int last, int &fir, int &cnt, int &sum, int &maxsum1, int &maxsum2){
    if(!x){
        fir = fir ^ 1;
        if(last == 1){
            maxsum1 -= 7;
        }
    }else{
        sum += x;
        if(!cnt && last == 1){
            maxsum1 -= 7;
        }else if(!cnt && last != 1){
            maxsum1 -= x;
            maxsum2 -= x;
        }else{
            if(x == 1){
                maxsum1 -= 1;
                maxsum2 -= 8;
                --cnt;
            }else{
                maxsum1 -= 7;
            }
        }
    }
}

int main(){
    int n;
    while(~scanf("%d",&n)){
        int cnt = 15;
        int sum1 = 0, sum2 = 0;
        int maxsum1 = 147, maxsum2 = 147;
        int fir = 1, ok = 1, tie = 0;
        int ans = n;
        int x, last = -1;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &x);
            if(fir && ok && !tie){
                update(x, last, fir, cnt, sum1, maxsum1, maxsum2);
            }else if(!fir && ok && !tie){
                update(x, last, fir, cnt, sum2, maxsum2, maxsum1);
            }
            if(!maxsum1 && !maxsum2 && sum1 == sum2){
                ok = 0, tie = 1;
                ans = n;
            }
            if(ok && !tie){
                if(sum1 > sum2 + maxsum2){
                    ans = i;
                    ok = 0;
                }else if(sum1 + maxsum1 < sum2){
                    ans = i;
                    ok = 0;
                }
            }
            last = x;
        }
        printf("%d\n", ans);
    }
    return 0;
}