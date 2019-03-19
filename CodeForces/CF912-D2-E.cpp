/* 
 https://codeforces.com/blog/entry/56920
*/ 

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N = 18, INF = 1e18;
ll n, k, p[N];
vector<ll> a, b;

void generate(vector<ll> &v, ll num, int id){
    if(num > INF)return ;

    if(id >= n){
        v.push_back(num); return ; 
    }

    for(ll val = num;val <= INF;){
        generate(v, val, id + 2);

        if(val <= INF/ p[id])val *= p[id];
        else break;
    }
}

bool F(ll x){
    ll cnt = 0;

    for(ll i =0, j = (ll)b.size() - 1; i < a.size();++i){
        while(j >= 0 && b[j] >= (x + a[i] - 1)/ a[i])j--;

        if(j < 0)break;
        cnt += (j + 1);
    }
    return cnt + 1 <= k;
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=0;i<n;++i)cin>>p[i];

    generate(a, 1, 0);
    generate(b, 1, 1);


    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    cin>>k;

    ll low = 1, high = INF + 1;
    while(high - low > 1){
        ll mid = (low + high)/2;
        F(mid)? low = mid : high = mid;
    }

    cout<<low<<"\n";
    return 0;
}
