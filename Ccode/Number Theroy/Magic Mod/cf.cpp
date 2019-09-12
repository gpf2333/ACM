#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int up = a * d - b * c, down;
    if(up > 0)  down = a * d;
    else down = b * c;
    up = abs(up);
    int g = gcd(up, down);
    up /= g,down /= g;
    cout << up << "/" << down << endl;
    return 0;
}