#include<bits/stdc++.h>
using namespace std;

bool cmp(const string &a, const string &b){
    if(a[1] == b[1]) return a[0] < b[0];
    return a[1] < b[1];

}

int calc(string str[]){
    if(str[0] == str[1] && str[1] == str[2]) return 0;
    if(str[0][1] == str[1][1] && str[0][1] == str[2][1]){
        if(str[0][0] == str[1][0] - 1 && str[1][0] + 1 == str[2][0]){
            return 0;
        }
        else if(str[0][0] == str[1][0] - 2 || str[1][0] + 2 == str[2][0]){
            return 1;
        }
        else if(str[0][0] == str[1][0] - 1 || str[1][0] + 1 == str[2][0]){
            return 1;
        }
    }
    if(str[0][1] == str[1][1]){
        if(str[0][0] == str[1][0] - 1 || str[0][0] == str[1][0] || str[0][0] + 2 == str[1][0]){
            return 1;
        }
    }
    if(str[1][1] == str[2][1]){
        if(str[1][0] == str[2][0] - 1 || str[1][0] == str[2][0] || str[1][0] + 2 == str[2][0]){
            return 1;
        }
    }
    return 2;
}

int main(){
    string str[10];
    for(int i = 0; i < 3; ++i){
        cin >> str[i];
    }
    sort(str, str + 3, cmp);
    int ans = calc(str);
    cout << ans << endl;
    return 0;
}