#include<bits/stdc++.h>
using namespace std;
const int maxn = 20000 + 10;
char s[maxn];
int calc(const int i, const int j, const int len, const int m){
    int res = 0, l = 0, r = 0, sum = 0;
    while(i - r >= 0 && j + r < len){
        int tmp = abs(s[i - r] - s[j + r]);
        if(sum +  tmp <= m){
            ++r;
            sum += tmp;
            res = max(res, r - l);
        }else{
            sum -= abs(s[i - l] - s[j + l]);
            ++l;
        }
    }
    return res;
}
int main(){
    int T, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d", &m);
        scanf("%s",s);
        int ans = 0, len = strlen(s);
        for(int i = 0; s[i]; ++i){
            ans = max(ans, max(calc(i - 1, i, len, m), calc(i - 1, i + 1, len, m)));
        }
        printf("%d\n", ans);
    }
    return 0;
}