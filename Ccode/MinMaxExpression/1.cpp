#include<bits/stdc++.h>
using namespace std;
unordered_map<string, bool>mp;

void getMin(const string &str, string &tmp){
    int i = 0, j = 1, k = 0;
    int len = str.size();
    while(i < len && j < len && k < len){
        int tmp = str[(i + k) % len] - str[(j + k) % len];
        if(!tmp) ++k;
        else{
            if(tmp > 0) i = i + k + 1;
            else j = j + k + 1;
            if(j == i) ++j;
            k = 0; 
        }
    }
    int p = min(i, j);
    tmp.clear();
    for(int i = 0; i < len; ++i){
        tmp.push_back(str[(i + p) % len]);
    }
}

int main(){
    ios::sync_with_stdio(NULL);
    cin.tie(0), cout.tie(0);
    int n;
    while(cin >> n){
        mp.clear();
        string s, tmp;
        int ans = 0;
        for(int i = 0; i < n; ++i){
            cin >> s;
            getMin(s, tmp);
            if(mp.count(tmp)) continue ;
            else mp[tmp] = 1, ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}