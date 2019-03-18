/* https://codeforces.com/blog/entry/7329 */

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

inline void add(int &a, int b){
    a += b;
    if(a >= MOD)a -= MOD;
}

inline void sub(int &a, int b){
    a -= b;
    if(a < 0)a += MOD;
}

inline int mul(int a, int b){
    return (int)((long long )a * b %MOD);
}

const int N = 55, INF = 1e9;
struct Data{
    int a, b, d;
};

queue<Data> q;
int n, k, one, two, level[N][N][2], ans[N][N][2], fac[N];

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

inline int C(int n, int k){
    return mul(fac[n], inv(mul(fac[k], fac[n - k])));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    fac[0] = 1;
    for(int i=1;i<N;++i)fac[i] = mul(fac[i - 1], i);

    cin>>n>>k; k/= 50;
    for(int i=0;i<n;++i){
        int x; cin>>x;
        if(x == 50)one++;
        else two++;
    }

    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            level[i][j][0] = level[i][j][1] = INF;


    q.push({one, two, 0});
    level[one][two][0] = 0, ans[one][two][0] = 1;

    while(!q.empty()){
        auto p = q.front(); q.pop();
        int a = p.a, b = p.b, d = p.d;

        if(d == 0){
            for(int i = 0; i <= a;++i)
                for(int j=0; j <= b && i + 2*j <= k; ++j)if(i + j){
                    int nxa = a - i, nxb = b - j;
                    if(level[nxa][nxb][1] > 1 + level[a][b][0]){
                        q.push({nxa, nxb, 1});
                        level[nxa][nxb][1] = 1 + level[a][b][0];
                        ans[nxa][nxb][1] = mul(ans[a][b][d], mul(C(a, i), C(b, j)));
                    }
                    else if(level[nxa][nxb][1] == 1 + level[a][b][0]){
                        add(ans[nxa][nxb][1],mul(ans[a][b][d], mul(C(a, i), C(b, j)) ) );
                    }
                }
        }
        else{
            for(int i=0;i<=one - a;++i)
                for(int j=0;j <= two - b && i + 2*j <= k;++j)if(i + j){
                    int nxa = a + i, nxb = b + j;
                    if(level[nxa][nxb][0] > 1 + level[a][b][1]){
                        level[nxa][nxb][0] = 1 + level[a][b][1];
                        q.push({nxa, nxb, 0});
                        ans[nxa][nxb][0] = mul(ans[a][b][d], mul(C(one - a, i), C(two - b, j)) );
                    }
                    else if(level[nxa][nxb][0] == 1 + level[a][b][1]){
                        add(ans[nxa][nxb][0], mul(ans[a][b][d], mul(C(one - a, i), C(two - b, j))) );
                    }
                }
        }
    }

    if(level[0][0][1] == INF)cout<<-1<<"\n";
    else cout<<level[0][0][1]<<"\n";
    cout<<ans[0][0][1]<<"\n";

    return 0;
}
