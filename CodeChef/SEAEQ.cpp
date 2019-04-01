/*
  Find first, dp[n][E] = number of permutations of [n] having exactly E inversions.
  dp[n][E] = Sigma j = (1, i) dp[n - 1][E - (n - j)], j is the last element in permutations.
  User prefix sums to calculate dp[n][E]
  
  Now, consider p1[l, r], where r - l = k. 
  Choose k elements in nCk ways, you can permute them with atmost E inversions in dp[k][E] ways, then the rest of elements can be permuted in (n - k)! ways
  Now, position of l can be chosen in (n - k + 1) ways.
  Now, choose k elements in p2, in nCk ways, their order is already fixed by p1[l..r]
  Rest n - k elements in p2 can be permuted in (n - k)! ways
  Therefore total number of p1[l..r] with r - l = k, is nCk * nCk * (n - k)! *(n - k)! * prefix[k][E]
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

const int N = 502;
int dp[N][N*N], prefix[N][N*N], fac[N], mx[N];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    dp[0][0] = prefix[0][0] = 1;
    for(int i=1;i<N;++i)mx[i] = i*(i - 1)/2;

    for(int i=1;i<N;++i){
        prefix[i][0] = dp[i][0] = 1;

        for(int j=1;j<= mx[i];++j){
            if(j - i + 1 <= mx[i - 1]){
                dp[i][j] = add(dp[i][j], prefix[i - 1][min(j,mx[i - 1])]);
            }
            if(j - i >= 0)dp[i][j] = sub(dp[i][j], prefix[i - 1][j - i]);

            prefix[i][j] = add(dp[i][j], prefix[i][j - 1]);
        }
    }


    fac[0] = 1;
    for(int i=1;i<N;++i)fac[i] = mul(i, fac[i - 1]);

    int t; cin>>t;
    while(t--){
        int n, e; cin>>n>>e;

        e = min(e, n*n);

        int res = 0;
        for(int i=1;i<=n;++i){
            int val = inv(mul(fac[i], fac[i]));
            val = mul(val, prefix[i][min(mx[i],e)]);
            val = mul(val, n - i + 1);
            res = add(res, val);
        }
        res = mul(res, mul(fac[n], fac[n]));
        cout<<res<<"\n";
    }
    return 0;
}
