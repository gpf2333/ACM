#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
string a,b,c;
string s[5];

int solve(){
    if(s[0]==s[1]&&s[1]==s[2]) return 0;
    if(s[0][0]==s[1][0]&&s[2][0]==s[1][0]){
        if(s[0][1]==s[1][1]-1&&s[2][1]==s[1][1]+1) return 0;
        if(s[0][1]==s[1][1]-1||s[2][1]==s[1][1]+1) return 1;
        if(s[0][1]==s[1][1]-2||s[2][1]==s[1][1]+2) return 1;
    }
    if(s[0][0]==s[1][0]){
        if(s[0][1]==s[1][1]-1||s[0][1]==s[1][1]-2||s[0][1]==s[1][1]) return 1;
    }
    if(s[2][0]==s[1][0]){
        if(s[1][1]==s[2][1]-1||s[1][1]==s[2][1]-2||s[1][1]==s[2][1]) return 1;
    }
    return 2;
    
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    string a,b,c;cin>>a>>b>>c;
    for(int i=0;i<3;i++) s[i]="";
    s[0]+=a[1];s[0]+=a[0];s[1]+=b[1];s[1]+=b[0];s[2]+=c[1];s[2]+=c[0];
    sort(s,s+3);
    cout<<solve()<<endl;
}