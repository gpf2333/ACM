#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 500000 + 100;

const int mx = 26;
struct Palindromic_Tree{
    int ch[maxn][mx];  //编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（儿子）。
    int f[maxn];   // 节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串。
    int len[maxn]; // 编号为i的节点表示的回文串的长度（一个节点表示一个回文串）。
    int s[maxn];    //第i次添加的字符（一开始设S[0] = -1，也可以是任意一个在串S中不会出现的字符）。
    int cnt[maxn]; //节点表示的本质不同的回文串的个数,调用count()函数之后
    int num[maxn]; //节点表示的最长回文串的最右端点为回文串结尾的回文串个数
    int last;  //新添加一个字母后所形成的最长回文串表示的节点。
    int sz;  //添加的节点个数。
    int n;  //添加的字符个数。
    int trans[maxn]; //表示小于等于当前节点i长度一半的最长回文后缀

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
    void add(int c){
        c -= 'a';
        s[++n] = c;
        int u = get_fail(last);
        if(!ch[u][c]){
            int np = newnode(len[u] + 2);
            f[np] = ch[get_fail(f[u])][c];
            num[np] = num[f[np]] + 1;
            ch[u][c] = np;
            if(len[np] <= 2){
                trans[np] = f[np];
            }else{
                int tmp = trans[u];
                while(s[n - len[tmp] - 1] != s[n] || ((len[tmp] + 2)  << 1) > len[np]){
                    tmp = f[tmp];
                }
                trans[np] = ch[tmp][c]; 
            }
        }
        last = ch[u][c];
        ++cnt[last];
    }
    int count(){
        int ans = 0;
        for(int i = sz - 1; ~i; --i) cnt[f[i]] += cnt[i];
        for(int i = 2; i < sz; ++i){
            if((len[trans[i]] << 1) == len[i] && (len[trans[i]] % 2 == 0)){
                ans = max(ans, len[i]);
            }
        }
        return ans;
    }
}pam;

char s[maxn];

int main(){
    int n;
    while(~scanf("%d", &n)){
        scanf("%s", s);
        int len = n;
        pam.init();
        for(int i = 0; i < len; ++i){
            pam.add(s[i]);
        }
        printf("%d\n", pam.count());
    }
    return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef unsigned long long ull;
// const int maxn = 500000 + 100;

// const int p = 19260817;
// const int mod = 469762049;

// ull Hash[maxn], pw[maxn];

// void init(){
//     pw[0] = 1;
//     for(int i = 1; i < maxn; ++i){
//         pw[i] = pw[i - 1] * p;
//     }
// }

// ull gethash(int l, int r){
//     if(!l) return Hash[r];
//     return (Hash[r] - Hash[l - 1] * pw[r - l + 1]);
// }

// bool check(int l, int r){
//     int mid = (l + r) >> 1;
//     int len = r - l + 1;
//     if(len & 1){
//         return gethash(l, mid) == gethash(mid, r);
//     }else{
//         return gethash(l, mid) == gethash(mid + 1, r);
//     }
// }

// //题意：给定一个字符串S，求长度1-|s|的所有本质不同的回文串，同时回文串前半部分也是回文串
// //solution：直接跑回文自动机，统计本质不同的回文串个数，并多开一个pos数组记录该回文串在数组中出现的下标
// // 回文串前半部分也是回文串则利用字符串哈希进行解决
// const int mx = 26;
// struct Palindromic_Tree{
//     int ch[maxn][mx];  //编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（儿子）。
//     int f[maxn];   // 节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串。
//     int len[maxn]; // 编号为i的节点表示的回文串的长度（一个节点表示一个回文串）。
//     int s[maxn];    //第i次添加的字符（一开始设S[0] = -1，也可以是任意一个在串S中不会出现的字符）。 
//     int cnt[maxn]; //节点表示的本质不同的回文串的个数,调用count()函数之后
//     int num[maxn]; //节点表示的最长回文串的最右端点为回文串结尾的回文串个数
//     int last;  //新添加一个字母后所形成的最长回文串表示的节点。 
//     int sz;  //添加的节点个数。
//     int n;  //添加的字符个数。
//     int pos[maxn];
    
//     int newnode(int x){
//         for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
//         cnt[sz] = num[sz] = 0, len[sz] = x;
//         return sz++;
//     }
//     void init(){
//         sz = 0;
//         newnode(0), newnode(-1);
//         last = n = 0, s[0] = -1, f[0] = 1;
//     }
//     int get_fail(int u){
//         while(s[n - len[u] - 1] != s[n]) u = f[u];
//         return u;
//     }
//     void add(int c){
//         c -= 'a';
//         s[++n] = c;
//         int u = get_fail(last);
//         if(!ch[u][c]){
//             int np = newnode(len[u] + 2);
//             f[np] = ch[get_fail(f[u])][c];
//             num[np] = num[f[np]] + 1;
//             ch[u][c] = np;
//         }
//         last = ch[u][c];
//         ++cnt[last];
//         pos[last] = n;
//     }
//     int count(){
//         int ans = 0;
//         for(int i = sz - 1; ~i; --i) cnt[f[i]] += cnt[i];
//         for(int i = 2; i < sz; ++i){
//             //cout << pos[i] << " " << pos[i] - len[i] << " " << pos[i] - 1 << endl;
//             if(len[i] % 4 == 0 && check(pos[i] - len[i], pos[i] - 1)){
//                 ans = max(ans, len[i]);
//             }
//         }
//         return ans;
//     }
// }pam;

// char s[maxn];

// int main(){
//     init();
//     int n;
//     while(~scanf("%d", &n)){
//         scanf("%s", s);
//         int len = n;
//         pam.init();
//         pam.add(s[0]); 
//         Hash[0] = s[0];
//         for(int i = 1; i < len; ++i){
//             pam.add(s[i]);
//             Hash[i] = (Hash[i - 1] * p + s[i]);
//         }
//         printf("%d\n", pam.count());
//     }
//     return 0;
// }