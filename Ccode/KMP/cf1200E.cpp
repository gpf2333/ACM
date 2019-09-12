#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
char ans[maxn], s[maxn];
int fail[maxn];

int main(){
    int n;
    while(~scanf("%d", &n)){
        scanf("%s", ans);
        int len = strlen(ans);
        for(int i = 2; i <= n; ++i){
            scanf("%s", s);
            int lens = strlen(s);
            int k = 0;
            fail[0] = fail[1] = 0;
            for(int j = 2; j <= lens; ++j){
                while(k && s[j - 1] != s[k]) k = fail[k];
                if(s[j - 1] == s[k]) ++k;
                fail[j] = k;
            }
            k = 0;
            for(int j = max(1, len - lens + 1); j <= len; ++j){
                while(k && ans[j - 1] != s[k]) k = fail[k];
                if(ans[j - 1] == s[k]) ++k;
            }
            for(int j = k; j < lens; ++j) ans[len++] = s[j];
            ans[len] = '\0';
        }
        puts(ans);
    }
    return 0;
}