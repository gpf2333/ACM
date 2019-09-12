#include<bits/stdc++.h>
using namespace std;

int calc(int n){
    int res = 0;
    for(int i = 1; i < n; ++i){
        for(int j = i + 1; j <= n; ++j){
            res += (i + j);
        }
    }
    return res;
}

int main(){
    for(int i = 1; i <= 10; ++i){
        cout << calc(i) << endl;
    }    
    return 0;
}