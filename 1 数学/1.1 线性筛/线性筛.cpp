#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool isprime[maxn]; //是否是素数
int cntp, prime[maxn]; //素数个数， 素数表
int mu[maxn], phi[maxn]; //莫比乌斯函数， 欧拉函数
void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    mu[1] = phi[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j]; 
                break ;
            }
            mu[i * prime[j]] = -mu[i];
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}

int d[maxn], e[maxn]; // d正除数个数， e最小质因子个数
void CalcD(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    d[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            e[i] = 1, d[i] = 2;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                e[i * prime[j]] = e[i] + 1;
                d[i * prime[j]] = d[i] / (e[i] + 1) * (e[i] + 2);
                break ;
            }
            e[i * prime[j]] = 1;
            d[i * prime[j]] = 2 * d[i];
        }
    }
}

int main(){
    return 0;
}