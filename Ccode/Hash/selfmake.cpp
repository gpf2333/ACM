#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct HASH {
    static const int mod = 12000005;
    int hs[mod], head[mod], nxt[mod], id[mod], top;
 
    void init(){
        memset(head, -1, sizeof(head));
        top = 1;
    };
 
    void insert(ll x, int y) {
        int k = x % mod;
        hs[top] = x, id[top] = y, nxt[top] = head[k], head[k] = top++;
    }
 
    int find(int x) {
        int k = x % mod;
        for (int i = head[k]; i != -1; i = nxt[i]) if (hs[i] == x) return id[i];
        return -1;
    }
}mp;

int main(){
    
    return 0;
}