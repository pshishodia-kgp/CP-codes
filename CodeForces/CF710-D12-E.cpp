/*
Hint :  after a double operation more than 1, + or - operation aren't optimal
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e7 + 5;
ll dp[N], n, x, y;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>x>>y;
    dp[1] = x;
    for(int i=2;i<=n;++i){
        dp[i] = dp[i - 1] + x;
        if(i & 1)dp[i] = min(dp[i], dp[(i + 1)/2] + y + x);
        else dp[i] = min(dp[i], dp[i/2] + y);
    }
    cout<<dp[n]<<"\n";
    return 0;
}
