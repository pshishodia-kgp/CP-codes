/*
    if (l, s) will be superior iff a[i] >=  max(a[(i + ks)mod n] ]) for all l <= i <= l + s - 1, where k can take value from 0 to infinity.
    Therefore a[i] must be maximum among all a[(i + ks)mod n]
    Group numbers, into lists, such that, a[i] and a[j] are in same list iff j - i = ks mod n
    Now we do not need to check answers for all s, but just the factors of n
    As if the  lists for s will be same as for gcd(s, n)
    
    Time complexity = O(n * d(n)) = (n^4/3)
    d(n) = number of divisors of n
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
int n, a[N];
vector<int> res[N];
long long ans;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin>>n;
    for(int i=0;i<n;++i)cin>>a[i];

    for(int s=1;s <n;++s){
        int gcd = __gcd(s, n);
        if(n%s != 0){
            ans += res[gcd][s/gcd];
            continue;
        }

        int sz = 0;
        for(int j=s;j<=n;j += s)sz++;
        res[s] = vector<int> (sz + 2);

        vector<int>  id(2*n);
        for(int i=0;i<s;++i){
            int mx = 0;
            for(int j=i;j<n;j += s)mx = max(mx, a[j]);

            for(int j=i;j<n;j += s)if(a[j] == mx)
                id[j] = id[n + j] = 1;
        }

        vector<int> prefix(2*n);
        for(int i=2*n-2; i>=0;--i){
            if(id[i])prefix[i] = 1 + prefix[i + 1];
            prefix[i] = min(prefix[i], n);
        }

        for(int i=0;i<n;++i){
            res[s][prefix[i]/s]++;
        }

        for(int i=sz;i>=1;--i)res[s][i] += res[s][i + 1];
            
        ans += res[s][1];
    }

    cout<<ans<<"\n";
    return 0;
}
