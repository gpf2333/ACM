#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
const int maxn = 5e6 + 10;
int n, p, q, m; 
unsigned int SA, SB, SC, mx;
unsigned int rng61(){ 
    SA ^= SA << 16; 
    SA ^= SA >> 5; 
    SA ^= SA << 1; 
    unsigned int t = SA; 
    SA = SB; 
    SB = SC; 
    SC ^= t ^ SA; 
    return SC;
}
ui sta[maxn][2];
int st[maxn][2];
int top = 0, tot = 0;
int main(){
    int T, cas = 0;
    ui x, mx;
    ll ans = 0;
    scanf("%d", &T);
    while(T--){
        cin >> n >> p >> q >> m >> SA >> SB >> SC;
        ans = top = tot = 0;
        int id;
        for(int i = 1; i <= n; ++i){
            if(rng61() % (p + q) < p){
                x = rng61() % m + 1;
            }else{
                x = 0;
            }
            if(x == 0){
                if(!top) mx = 0;
                else{
                    x = sta[top][0], id = sta[top][1];
                    --top;
                    if(id > st[tot][1]){
                        mx = st[tot][0];
                    }else if(id == st[tot][1]){
                        --tot;
                        if(tot == 0) mx = 0;
                        else mx = st[tot][0];
                    }
                }
            }else{
                sta[top++][0] = x;
                sta[top][1] = i;
                if(tot == 0){
                    mx = x;
                    st[++tot][0] = x;
                    st[tot][1] = i;
                }else{
                    if(x >= st[tot][0]){
                        mx = x;
                        st[++tot][0] = x;
                        st[tot][1] = i;
                    }else{
                        mx = st[tot][0];
                    }
                }
            }
            ans ^= (ll)i * mx;
        }
        printf("Case #%d: %lld\n", ++cas, ans);
    }
    return 0;
}