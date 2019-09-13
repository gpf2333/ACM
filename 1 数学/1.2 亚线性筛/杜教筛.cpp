#include<bits/stdc++.h>
#include<tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
// O(n ^ 2 / 3) 时间求积性函数的前缀和
const int maxn = 1e7;
bool isprime[maxn + 5];
int prime[maxn],cntp,mu[maxn];
ll phi[maxn];
tr1::unordered_map<int, int>mpu; //代替map，加快速度
tr1::unordered_map<int, ll>mpp; 
void init(){
    memset(isprime,1,sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    phi[1] = mu[1] = 1;
    cntp = 0;
    for(int i = 2; i <= maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i, phi[i] = i - 1, mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] <=maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j],
                mu[i * prime[j]] = 0;
                break ;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }
    }
    //根据题目要求需要改动
    for(int i = 2; i <= maxn; ++i){
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}
//分块+记忆化
int calc_mu(int x){
    if(x <= maxn) return mu[x];
    if(mpu.count(x)) return mpu[x];
    int res = 1;
    for(unsigned int l = 2,r;  l <= x; l = r + 1){ //可能爆int，比如r = 2147483647
        r = x / (x / l);
        res -= calc_mu(x / l) * (r - l + 1);
    }
    return mpu[x] = res;
}

ll calc_phi(int x){
    if(x <= maxn) return phi[x];
    if(mpp.count(x))  return mpp[x];
    ll res =  1LL * x * (x + 1) / 2;
    for(unsigned int l = 2, r; l <= x; l = r + 1){ //可能爆int，比如r = 2147483647
        r = x / (x / l);
        res -= calc_phi(x / l) * (r - l + 1);
    }
    return mpp[x] = res;
}

int main(){
    init();
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%lld %d\n", calc_phi(n), calc_mu(n));
    }
    return 0;
}
