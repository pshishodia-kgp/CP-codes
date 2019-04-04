/*
  Approach same as editorial.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define sz(a) (int)((a).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second
#define mp make_pair
// defines end

const int MOD = 1e9 + 7;

// Functions starts from here

inline int add(int a, int b){
    a += b;
    if(a >= MOD)a -= MOD;
    return a;
}

inline int sub(int a, int b){
    a -= b;
    if(a < 0)a += MOD;
    return a;
}

inline int mul(int a, int b){
    return (int)((long long) a * b %MOD);
}

inline int binpow(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1)res = mul(res, a);
        a = mul(a, a);
        b /= 2;
    }
    return res;
}

inline int inv(int a){
    return binpow(a, MOD - 2);
}

// Template ends here 
// Code starts from here

const int N = 1e5 + 5;
int n, dp[N];
vector<int> prime[N];

void sieve(){
    vector<int> vis(N);

    for(int i=2;i<N;++i)if(!vis[i])
        for(int j=i;j<N;j += i){
            vis[j] = 1;
            prime[j].push_back(i);
        }
}

int find(int id, int val, vector<int> &v, int m){
    if(id == (int)v.size())return m/val;

    return find(id + 1, val, v, m) + find(id + 1, -1*val*v[id], v, m);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    sieve();
    cin>>n;

    dp[1] = 0;
    for(int i=2;i<=n;++i){
        dp[i] = mul(dp[i], inv(n));
        dp[i] = add(dp[i], 1);
        int den = sub(1, mul(n/i, inv(n)));
        dp[i] = mul(dp[i], inv(den));


        for(int j=2*i; j <= n;j += i){
            dp[j] = add(dp[j], mul(dp[i], find(0, 1, prime[j/i], n/i)) );
        }
    }

    int ans = 0;
    for(int i=1;i<=n;++i){
        ans = add(ans, dp[i]);
    }
    ans = add(1, mul(ans, inv(n)));

    cout<<ans<<"\n";
    return 0;
}
