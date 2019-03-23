/* 
  suppose we assign x[i][j] ( = 0, or 1) to box (i, j) depending on if it contains treasure or not. Then the question will reduce to 
  finding solution of linear equation modulo 2. 
  This can be done by gaussian elimination (find rank) in O((n*m)^3)
  Use bitset to reduce it to O((n*m)^3 / 32)
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

const int N = 900;
int a[31][31], n, m;
bitset<N> bs[N];
bool mat[N];

inline int find(int i, int j){
    if(i < 0 || i >= n || j < 0 || j >= m)return -1;
    return i*m + j;
}

inline int mul(int a, int b){
    return (int)((long long)a * b %MOD);
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

int gaussianElimination(){
    int sz = n*m;

    for(int piv = 0, i = 0;piv < sz; ++piv){
        for(int j=i;j<sz;++j)if(bs[j][piv]){
            swap(bs[i], bs[j]); swap(mat[i], mat[j]);
            break;
        }

        if(!bs[i][piv])continue;

        for(int j = i + 1;j < sz;++j)if(bs[j][piv])
            bs[j] ^=  bs[i], mat[j] ^= mat[i];

        ++i;
    }
    int rnk = 0;
    for(int i=0;i<sz;++i){
        if(bs[i].none()){
            if(mat[i])return -1;
        }
        else rnk++; 
    }
    return rnk;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin>>t;
    while(t--){
        for(int i=0;i<900;++i)bs[i].reset(), mat[i] = 0;
        
        cin>>n>>m;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j){
                cin>>a[i][j]; 
                if(a[i][j] == -1)continue;

                if(find(i - 1, j) != -1)bs[find(i, j)][find(i - 1, j)] = 1;
                if(find(i + 1, j) != -1)bs[find(i, j)][find(i + 1, j)] = 1;
                if(find(i, j - 1) != -1)bs[find(i, j)][find(i, j - 1)] = 1;
                if(find(i, j + 1) != -1)bs[find(i, j)][find(i, j + 1)] = 1;

                mat[find(i, j)] = a[i][j]; 
            }

        int rnk = gaussianElimination();
        if(rnk == -1)cout<<"0\n";
        else cout<<binpow(2, n*m - rnk)<<"\n";
    }
    return 0;
}
