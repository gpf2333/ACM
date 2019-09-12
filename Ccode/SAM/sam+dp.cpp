#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;

const int mx = 26;
struct SAM{
    int ch[maxn << 1][mx], len[maxn << 1], link[maxn << 1];
    int sz, last;
    inline void init(){
        sz = 1, last = 1;
        len[1] = link[1] = 0;
        for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
    }
    void add(int c){
        //c -= 'a';
        int p, np = ++sz;
        for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
        len[np] = len[last] + 1;
        for(p = last; p && !ch[p][c]; p = link[p]){
            ch[p][c] = np;
        }
        if(!p){
            link[np] = 1;
        }
        else{
            int q = ch[p][c];
            if(len[q] == len[p] + 1){
                link[np] = q;
            }else{
                int nq = ++sz;
                for(int i = 0; i < mx; ++i) ch[sz][i] = 0;
                len[nq] = len[p] + 1;
                for(int i = 0; i < mx; ++i){
                    ch[nq][i] = ch[q][i];
                }
                for(; p && ch[p][c] == q; p = link[p]){
                    ch[p][c] = nq;
                }
                link[nq] = link[q];
                link[q] = link[np] = nq;
            }
        }
        last = np;
    }
}sam;

char s[maxn];
ll dp[maxn];

/*
solution: 对于i，维护一个j满足s[j+1...i]是s[1--j]的一个子集, 也就是说s[j+1...i]可以由s[1--j]的子集
A: dp[i] = dp[i - 1] + p;
B: dp[i] = dp[j] + q;
dp[i] = min(A, B)
关键点: 维护一个j
i,j关系可以通过sam来维护
对于一个满足条件的j, 记录其在后缀自动机上最后出现的位置cur,
每次i或者j出现变化的时候,检查cur的后缀链接link指向的终点集合位置的长度是否大于等于匹配长度i-j-1.
符合条件则继续想着后缀链接跳继续匹配
*/

int main(){
    while(~scanf("%s", s + 1)){
        int p, q;
        scanf("%d%d", &p, &q);
        sam.init();
        int len = strlen(s + 1);
        dp[1] = p;
        int c = s[1] - 'a';
        sam.add(c);
        int j = 1, cur = sam.ch[1][c];
        for(int i = 2; i <= len; ++i){
            c = s[i] - 'a';
            dp[i] = dp[i - 1] + p;
            while(1){
                while(cur != 1 && sam.len[sam.link[cur]] >= i - j - 1) cur = sam.link[cur];
                if(sam.ch[cur][c]){
                    cur = sam.ch[cur][c];
                    break ;
                }else{
                    sam.add(s[++j] - 'a');
                }
            }
            dp[i] = min(dp[i], dp[j] + q);
        }
        printf("%lld\n", dp[len]);
    }
    return 0;
}