#include <bits/stdc++.h>

using namespace std;

const int N = 63, MOD = 1e9 + 7;

inline void add(int &a, int b){
    a += b;
    if(a >= MOD)a -= MOD;
}

inline void sub(int &a, int b){
    a -= b;
    if(a < 0)a += MOD;
}

inline int mul(int a, int b){
    return (int)((long long ) a * b %MOD);
}

int n, dp[N][N][N][N][2]; 

int find(int l1, int l2, int l3, int l4, int flag, int lis){
    if(lis == 3 && l4 > 0)return 0;

    if(lis == 3 && l3)flag = 1;
    if(lis == 4 && l4)flag = 1;

    if(lis == 3 && l1 + l2 == 0)return flag;
    if(lis == 4 && l1 + l2 + l3 == 0)return flag;

    if(dp[l1][l2][l3][l4][flag] != -1)return dp[l1][l2][l3][l4][flag];

    int val = 0;
    for(int i=1;i<=l1;++i)add(val, find(i - 1, l2 + l1 - i, l3, l4, flag, lis) );

    for(int i=1;i<=l2;++i)add(val, find(l1, i - 1, l3 + l2 - i, l4, flag, lis) );

    for(int i=1;i<=l3; ++i)add(val, find(l1, l2, i - 1, l4 + l3 - i, flag, lis));

    if(l4 >= 1)add(val, find(l1, l2, l3, l4 - 1, flag, lis)); 

    dp[l1][l2][l3][l4][flag] = val;
    return val;
}

void reset(){
    for(int l1=0;l1 <=n;++l1)
        for(int l2=0;l2 <=n; ++l2)
            for(int l3= 0;l3 <= n;++l3)
                for(int l4 = 0; l4 <= n; ++l4)
                    dp[l1][l2][l3][l4][0] = dp[l1][l2][l3][l4][1] = -1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    int fac = 1;
    for(int i=1;i<=n;++i)fac = mul(i, fac);

    reset();    sub(fac, find(n, 0, 0, 0, 0,  3)); 
    reset();    sub(fac, find(n, 0, 0, 0, 0, 4));

    cout<<fac<<"\n";
    return 0;
}
