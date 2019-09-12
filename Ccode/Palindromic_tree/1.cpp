#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 100;

//题意：求字符串S的所有回文子串中，位置不相交的的回文串的对数。
// aaa 5 (1 1 2 2) (1 1 3 3) (1 1 2 3) (1 2,3 3) (2 2, 3 3)
// 利用pam中num[]数组记录字符串s中以i结尾的回文串个数
// 开一个数组l[i]表示以i结尾的回文串数目, 然后统计前缀和
// pam清空， 反向再统计以i为左端点的回文串数组，l[i - 1] * num[i]累加
const int mx = 26;
struct Palindromic_Tree{
    int ch[maxn][mx], f[maxn], len[maxn], s[maxn];
    int cnt[maxn];
    int num[maxn];
    int last, sz, n;
    int newnode(int x){
        for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
        cnt[sz] = num[sz] = 0, len[sz] = x;
        return sz++;
    }
    void init(){
        sz = 0;
        newnode(0), newnode(-1);
        last = n = 0, s[0] = -1, f[0] = 1;
    }
    int get_fail(int u){
        while(s[n - len[u] - 1] != s[n]) u = f[u];
        return u;
    }
    int add(int c){
        c -= 'a';
        s[++n] = c;
        int u = get_fail(last);
        if(!ch[u][c]){
            int np = newnode(len[u] + 2);
            f[np] = ch[get_fail(f[u])][c];
            num[np] = num[f[np]] + 1;
            ch[u][c] = np;
        }
        last = ch[u][c];
        ++cnt[last];
        return num[last];
    }
    void count(){
        for(int i = sz - 1; ~i; --i){
            cnt[f[i]] += cnt[i];
        }
    }
}pam;

char s[maxn];
int l[maxn];
int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        pam.init();
        l[0] = pam.add(s[0]);
        for(int i = 1; i < len; ++i){
            l[i] = l[i - 1] + pam.add(s[i]);
        }
        pam.init();
        long long ans = 0;
        for(int i = len - 1; i > 0; --i){
            ans += (long long)l[i - 1] * pam.add(s[i]); 
        }
        printf("%lld\n", ans);
    }
    return 0;
}