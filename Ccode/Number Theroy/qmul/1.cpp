#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ksc(ll x,ll y,ll mod)
{
    return (x * y - (ll)((long double) x / mod * y ) * mod + mod) % mod;
}
