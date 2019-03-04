/*
  Count number of subsequences whose front bracket end at i.
  Let m be number of open brackets before (including i), and n be the number of close brackets after i. 
  then number of subsequences = (m - 1)C0 * nC1 + (m - 1)C1*nC2 + ...... = (m + n - 1)C (n - 1)
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

const int N = 2e5 + 5;
int n, front[N], back[N], fac[N];

inline int C(int m, int r){
    return mul(fac[m], inv(mul(fac[r], fac[m - r])));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; cin>>s; 
    n = s.size();
    s = '*' + s;

    fac[0] = 1;
    for(int i=1;i<N;++i)fac[i] = mul(fac[i - 1], i);

    for(int i=1;i<=n;++i){
        if(s[i] == '(')front[i] = 1;
        front[i] += front[i - 1];
    }
    for(int i=n;i>=1;--i){
        if(s[i] == ')')back[i] = 1;
        back[i] += back[i + 1];
    }

    int ans = 0;
    for(int i=1;i<=n;++i)if(s[i] == '('){
        if(back[i] >= 1)ans = add(ans, C(front[i] + back[i] - 1, back[i] - 1));
    }
    cout<<ans<<"\n";
    return 0;
}
