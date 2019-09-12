#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
bool isprime[maxn];
int cntp, prime[maxn];
int fac[maxn][20];
bool active[maxn];
int rel[maxn];

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0) break ;
        }
    }
}

void calc(const int n){
    int x = n;
    int &len = fac[x][0];
    for(int i = 1; i <= cntp && prime[i] <= x; ++i){
        if(x % prime[i] == 0){
            fac[n][++len] = prime[i];
            while(x % prime[i] == 0) x /= prime[i];
        }
    }
    if(x > 1){
        fac[n][++len] = x;
    }
}

void act(int x){
    if(active[x]){
        puts("Already on"); return ;
    }else{
        for(int i = 1; i <= fac[x][0]; ++i){ 
            if(rel[fac[x][i]]){
                printf("Conflict with %d\n", rel[fac[x][i]]);
                return ;
            }
        }
        active[x] = 1;
        for(int i = 1; i <= fac[x][0]; ++i){
            rel[fac[x][i]] = x;
        }
        puts("Success");
    }
}

void dea(int x){
    if(!active[x]){
        puts("Already off"); return ;
    }else{
        active[x] = 0;
        for(int i = 1; i <= fac[x][0]; ++i){
            rel[fac[x][i]] = 0;
        }
        puts("Success");
    }
}

int main(){
    init();
    memset(active, 0, sizeof(active));
    memset(rel, 0, sizeof(rel));
    int n, m;
    char op[5];
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        calc(i);
    }
    while(m--){
        int x;
        scanf("%s%d", op, &x);
        if(op[0] == '+') act(x);
        else  dea(x);
    }
    return 0;
}