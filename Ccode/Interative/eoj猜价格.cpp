#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char query(const ll x){
    cout << x << endl;
    fflush(stdout);
    char c;
    cin >> c;
    return c;
}
int main(){
    int n, k;
    cin >> n >> k;
    ll l = 1, r = (1LL << n) - 1;
    if(n >= k){
        int cnt = 0;
        while(1){
            char c = query(1);
            if(c == '=') return 0;
            if(c != '<') break ;
        }
        while(l <= r){
            ll mid = (l + r) >> 1;
            char c = query(mid);
            if(c == '=') return 0;
            ++cnt;
            if(c == '<'){
                if(cnt == k) r = mid - 1, cnt = 0;
                else l = mid + 1;
            }else{
                if(cnt == k) l = mid + 1, cnt = 0;
                else r = mid - 1;
            }
        }
    }else{
        while(l <= r){
            ll mid = (l + r) >> 1;
            char a = query(mid);
            if(a == '=') return 0;
            char b = query(mid);
            if(b == '=') return 0;
            if(a == b){
                if(a == '<')l = mid + 1;
                else r = mid - 1;
            }else{
                while(l <= r){
                    ll c = query(mid);
                    if(c == '=') return 0;
                    if(c == '<') l = mid + 1;
                    else r = mid - 1;
                    mid = (l + r) >> 1;
                }
            }
        }
    }
    return 0;
}