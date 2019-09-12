#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

bool check(int x, int v){
    int res = x;
    int up = ceil(log2(x));
    for(int i = 1; i <= up; ++i){
        res -= x / (1 << (i));
    }
    return (res == v);
}

int func(int x){
    int res = 0;
    int up = ceil(log2(x));
    for(int i = 1; i <= up; ++i){
        res += x / (1 << (i));
    }
    return res;
}

int main(){
    // for(int i = 1; i <= 100; ++i){
    //     cout << i << " " << func(i) << endl;
    // }
    for(int i = 1; i <= 100000; ++i){
        if(check(i, 64)){
            cout << i << endl;
        }
    }
    return 0;
}