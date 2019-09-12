#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn = 1e6 + 10;
const int p = 11;
char s[maxn];
ull pw[maxn];
ull Hash[maxn];
int main(){
    while(~scanf("%s", s)){
        Hash[0] = 0; 
        pw[0] = 1;
        int len = strlen(s);
        for(int i = 1; i <= len; ++i){
            Hash[i] = Hash[i - 1] * p + (s[i - 1] - '0');
            pw[i] = pw[i - 1] * p;
        }
        ull ans = 0;
        int mid = (len % 2 == 0) ? (len / 2) : (len / 2 + 1);
        int st = 0, ed = 1;
        for( ; ed <= mid; ++ed){
            if((Hash[ed] - Hash[st] * pw[ed - st]) == (Hash[len - st] - Hash[len - ed] * pw[ed - st])){
                if(ed != len - st){
                    ans += 2;
                    st = ed;
                } else{
                    ++ans;
                }
            }
        }
        if(len - 2 * st > 1 || ans == 0){
            ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}