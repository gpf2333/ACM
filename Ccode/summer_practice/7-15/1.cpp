#include<bits/stdc++.h>
using namespace std;
const int maxn = 500;
int a[maxn];
int main(){
    string s, s1;
    cin >> s;
    for(int i = 0; i < s.length(); i += 2){
        if(s[i] == '<') s1.push_back('(');
        else s1.push_back(')');
    }
    memset(a, -1, sizeof(a));
    bool ok = true;
    stack<char>sta;
    for(int i = 0; i < s1.length(); ++i){
        if(!sta.empty()){
            if(sta.top() == s1[i]){
                sta.push(s1[i]);
            }else if(sta.top() != s1[i]){
                sta.pop();
                a[i] = 1;
            }
        }else{
            sta.push(s1[i]);
        }
    }
    if(!sta.empty()){
        puts("Keine Loesung");
        return 0;
    }
    for(int i = 0; i < s1.length(); ++i){
        if(a[i] == -1){
            putchar('[');
        }else{
            putchar(']');
        }
    }
    puts("");
    return 0;
}