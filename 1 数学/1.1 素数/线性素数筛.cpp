bool isprime[maxn];
int cntp, prime[maxn];
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