/*

给定n个整数，求其中异或和为0的子集的大小的和。
首先转化为每个可以通过异或表示0的数贡献它参与的子集数。
思考的过程分两步。一开始不管三七二十一先对n个整数求一次线性基B1，记其秩为 r.

第一步：
先考虑线性基B1外的数（假如有的话）产生的贡献。枚举每一个数，记这个数为x，除去这个数，线性基B1外还有n−r−1个数，
他们可以自由组合出2 ^ (n − r − 1) 种子集, 加上x本身之后，必定能被线性基B1表示，故这些子集都会使得x发生贡献。这样的x共有n−r个。

第二步：
再考虑线性基B1中的数产生的贡献。枚举每一个数，记这个数为x，这个数产生的贡献来源于他在第一步中被使用的次数。
那怎么判断这个数被使用了多少次呢？把除去这个数x的n−1个数求出线性基B3。
假如x能被线性基B3表示，则用不着x其他子集也可以组成0，也就是说，选择x之后不可能可以构造出异或和为0的子集。
否则，选择x之后，配上这个线性基B3，可以把除去x和B3的总共n−r−1个数，自由组合出的2 ^ n−r−1种子集都配成0。

第三步：
最后是快速得到B3的办法，注意到B3必定先通过除去B1的n−r个数构造，可以把n−r先构造出B2，然后再插入B1内除x的r−1个数构成。
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
const int mx = 63;
struct LinearBase{
    int rk;
    bool flag;
    ll base[mx + 1];

    void copy(const LinearBase &b){
        rk = b.rk, flag = b.flag;
        for(int i = 0; i < mx; ++i){
            base[i] = b.base[i];
        }
    }

    void clear(){
        rk = 0, flag = false;
        for(int i = 0; i < mx; ++i) base[i] = 0;
    }

    void insert(ll x){
        for(int i = mx; ~i; --i){
            if(x & (1LL << i)){
                if(!base[i]){
                    base[i] = x;
                    ++rk;
                    return ;
                }else{
                    x ^= base[i];
                }
            }
        }
        flag = true;
    }

    bool check(ll x){
        for(int i = mx; ~i; --i){
            if(x & (1LL << i)){
                if(!base[i]) return false;
                else x ^= base[i];
            }
        }
        return true;
    }

};

LinearBase B1, B2, B3;
vector<ll>vec;

ll fast_pow(ll a, int b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    int n;
    while(~scanf("%d", &n)){
        vec.clear();
        B1.clear(); B2.clear(); B3.clear();
        ll x;
        for(int i = 0; i < n; ++i){
            scanf("%lld", &x);
            if(B1.check(x)){
                B2.insert(x);
            }else{
                B1.insert(x);
                vec.push_back(x);
            }
        }
        ll ans = 0;
        if(B1.rk != n){
            ll tmp = fast_pow(2, n - B1.rk - 1);
            ans = (ans + tmp * (n - B1.rk) % mod) % mod;
        }
        ll tmp = fast_pow(2, n - B1.rk - 1);
        for(auto &x: vec){
            B3.copy(B2);
            for(auto &y: vec){
                if(x != y){
                    B3.insert(y);
                }
            }
            if(B3.check(x)){
                ans = (ans + tmp) % mod;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}