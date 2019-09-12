#include <bits/stdc++.h>
using namespace std;
int cai[10];
int hong;
int main()
{
    int n;
    cin>>n;
    hong = 15;
    int sum1 = 0;
    int sum2 = 0;
    int maxsum1 = 147;
    int maxsum2 = 147;
    bool flag = true;
    bool is = true;
    bool tie = false;
    int ans = n;
    int pre = - 1;
    for(int i = 1; i <= n; i++)
    {
        int t;
        cin>>t;
        if(flag && !tie && is)
        {
            if(!t)
            {
                flag = false;
                if(pre != -1)
                {
                    if(pre == 1)
                        maxsum1 -= 7;
                }
            }
            else
            {
                if(!hong&&pre!=1)
                {
                    sum1 += t;
                    maxsum2 -= t;
                    maxsum1 -= t;
                }
                else if(!hong && pre ==1)
                {
                    sum1 += t;
                    maxsum1 -= 7;
                }
                else
                {
                    sum1 += t;
                    if(t == 1)
                    {
                        maxsum2 -= 8;
                        maxsum1 -= 1;
                        hong--;
                    }
                    else
                    {
                        maxsum1 -= 7;
                    }
                }
            }
        }
        else if(!flag && !tie && is)
        {
            if(!t)
            {
                flag = true;
                if(pre != -1)
                {
                    if(pre == 1)
                    {
                        maxsum2 -= 7;
                    }
                }
            }
            else
            {
                if(!hong && pre != 1)
                {
                    sum2 += t;
                    maxsum2 -= t;
                    maxsum1 -= t;
                }
                else if(!hong && pre == 1)
                {
                    maxsum2 -= 7;
                    sum2 +=t;
                }
                else
                {
                    sum2 += t;
                    if(t == 1)
                    {
                        maxsum1 -= 8;
                        maxsum2 -= 1;
                        hong--;
                    }
                    else
                    {
                        maxsum2 -= 7;
                    }
                }
            }
        }
        if(maxsum1 ==0 && maxsum2 ==0 && is && !tie && sum1 == sum2)
        {
            tie = true;
            ans = n;
            is = false;
        }

        if(is && !tie)
        {
            if(sum1 < sum2)
            {
                if(sum1 + maxsum1 < sum2)
                {
                    ans = i;
                    is = false;
                }
            }
            else if(sum2 < sum1)
            {
                if(sum2 + maxsum2 < sum1)
                {
                    ans = i;
                    is = false;
                }
            }
        }
        pre = t;
    }
    cout << ans <<endl;
}