#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t i128;
#define times 6

long long total;
long long factor[110];

long long qmul(long long a,long long b,long long M){
    a%=M;
    b%=M;
    long long ans=0;
    while (b){
        if (b&1){
            ans=(ans+a)%M;
        }
        a=(a<<=1)%M;
        b>>=1;
    }
    return ans%M;
}

long long qpow(long long a,long long b,long long int M){
    long long ans=1;
    long long k=a;
    while(b){
        if(b&1)ans=qmul(ans,k,M)%M;
        k=qmul(k,k,M)%M;
        b>>=1;
    }
    return ans%M;
}

bool witness(long long a,long long n,long long x,long long sum){
    long long judge=qpow(a,x,n);
    if (judge==n-1||judge==1)return 1;
    while (sum--){
        judge=qmul(judge,judge,n);
        if(judge==n-1)  return 1;
    }
    return 0;
}

bool miller(long long n){
    if (n < 2)return 0;
    if (n == 2)return 1;
    if ((n & 1) == 0)return 0;
    long long x = n-1;
    long long sum = 0;
    while(x%2 == 0){
        x >>= 1;
        sum++;
    }
    srand(time(NULL));
    for (int i = 1; i <= times; i++){
        long long a = rand() % (n-1)+1;
        if (!witness(a,n,x,sum))return 0;
    }
    return 1;
}

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

long long pollard(long long n,long long c){
    long long x,y,d,i=1,k=2;
    x=rand()%n;
    y=x;
    while (1){
        i++;
        x=(qmul(x,x,n)+c)%n;
        d=gcd(y-x,n);
        if (d<0)d=-d;
        if (d>1&&d<n)   return d;
        if (y==x)return n;
        if (i==k){
            y=x;
            k<<=1;
        }
    }
}

void find(long long n){
    if (miller(n)){
        factor[++total] = n;
        return ;
    }
    long long p = n;
    while (p >= n){
        p = pollard(p, rand() % (n-1) + 1);
    }
    find(n / p);
    find(p);
}

int calc(ll n){
    total = 0;
    find(n);
    int ans = 200, c;
    for(int i = 1; i <= total; ++i){
        c = 0;
        cout << "!!" << factor[i] << endl;
        while((n % factor[i]) == 0){
            ++c;
            n /= factor[i];
        }
        ans = min(ans, c);
    }
    return ans;
}

ll get2(ll n){
    ll l = 1, r = n, ans = 1;
    while(l <= r){
        i128 mid = (l + r) >> 1;
        if(mid * mid <= n){
            ans = mid, l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return ans;
}

ll get3(ll n){
    ll l = 1, r = n, ans = 1;
    while(l <= r){
        i128 mid = (l + r) >> 1;
        if(mid * mid * mid <= n){
            ans = mid, l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return ans;
}

bool check2(ll n, ll &res){
    res = get2(n);
    return (res * res == n);
}

bool check3(ll n, ll &res){
    res = get3(n);
    return (res * res * res == n);
}

int main(){
    int T;
    ll n;
    scanf("%d",&T);
    while (T--){
        scanf("%lld",&n);
        if (miller(n)){
            puts("1");
        }
        else {
            ll tmp = n, tmp1, tmp2;
            int cnt1 = 0, cnt2 = 0;
            bool ok = 1, ok1, ok2;
            while((ok1 = check2(tmp, tmp1)) || (ok2 = check3(tmp, tmp2))){
                ok = 0;
                if(ok1){
                    tmp = tmp1, ++cnt1;
                }
                else if(ok2){
                    tmp = tmp2, ++cnt2;
                }
            }
            if(ok){
                cout << 1 << endl;
                printf("%d\n", calc(n));
            }else{
                int ans = calc(tmp);
                while(cnt1--){
                    ans *= 2;
                }
                while(cnt2--){
                    ans *= 3;
                }
                printf("%d\n",ans);
            }
        }
    }
}