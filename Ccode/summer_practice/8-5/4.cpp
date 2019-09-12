#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int a[maxn], b[maxn];
vector<int>vec[maxn];
int main(){
    int T = 100;
    mt19937 rnd(time(0));
    while(T--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; ++i){
            a[i] = rnd() % 20 + 1;
            b[i] = rnd() % 20 + 1;
        }
        
    }
    return 0;
}