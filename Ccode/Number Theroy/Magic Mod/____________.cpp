#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int a, b, c, pos = -1;
    cin >> a >> b >> c;
    for(int i = 1; i < maxn; ++i){
        a *= 10;
        if(a / b == c){
            pos = i; break ;
        }
        a %= b;
    }
    cout << pos << endl;
    return 0;
}