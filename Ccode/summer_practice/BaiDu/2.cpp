#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        if(n % 2 == 0) cout << (n + 1) << endl;
        else cout << (n - 1) << endl;
    }
    return 0;
}