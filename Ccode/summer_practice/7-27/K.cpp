#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
char s[maxn];
int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        bool flag1 = 0, flag2 = 0;
        ll res = 0;
        ll cnt = 0;
        ll ans = 0;
        ll las = -1;
        for(int i = len - 1; i >= 0; --i){
            if(!flag1 && s[i] == '0'){
                cnt = 1;
                flag1 = 1;
                if(las != -1){
                    ans += (cnt - 1);
                }
            }else if(flag1 && s[i] == '0'){
                ++cnt;
                if(las != -1){
                    ans += (cnt - 1);
                }
            }else if(flag1 && s[i] != '0'){
                if(!flag2){
                    ans += cnt * (cnt + 1) / 2;
                    flag2 = 1;
                }
                res += (s[i] - '0');
                res %= 3;
                if(res == 0){
                    ans += (cnt - 1);
                }
                if(i > 0 && s[i - 1] == '0'){
                    flag1 = 0; cnt = 0; flag2 = 0;
                    if(res % 3 == 0){
                        las = cnt;
                    }else{
                        las = -1;
                    }
                }
                if(!i) flag1 = 0;
                cout << i << " " << s[i] << " " << ans << endl;
            }
        }
        if(flag1){
            ans += cnt * (cnt + 1) / 2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}