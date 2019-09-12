#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
char s[maxn], t[maxn];
int ch[maxn][26];
int vis[maxn];

int main(){
    scanf("%s%s", s, t);
    int lens = strlen(s), lent = strlen(t);
    for(int j = 0; j < 26; ++j){
        ch[lens][j] = lens;
        vis[lens] = 0;
    }    
    int q = lent - 1, cnt = 0;
    for(int i = lens - 1; i >= 0; --i){
        if(s[i] == t[q]){
            ++cnt;
        }
        for(int j = 0; j < 26; ++j){
            ch[i][j] = ch[i + 1][j];
        }
        ch[i][s[i] - 'a'] = i;
    }
    return 0;
}