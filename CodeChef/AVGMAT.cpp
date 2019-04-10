/ * Rotate the grid by 45%, now the rhombus becomes a square.
Now use prefix sums 
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 305;
int a[2*N][2*N], p[2*N][2*N], ans[2*N];

inline int sum(int a, int b, int c, int d){
    return p[c][d] - p[c][b - 1] - p[a - 1][d] + p[a - 1][b - 1];
}
int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 

    int t; cin>>t;
    while(t--){
        int n, m; cin>>n>>m;

        for(int i=0;i<=n + m; ++i)
            for(int j=0;j<=n + m;++j)a[i][j] = p[i][j] = ans[i] = 0;

        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j){
                char x; cin>>x; 
                if(x == '1')a[i + j][i - j + m] = 1;
            }

        // calculate prefix sum 
        for(int i=1;i<=n + m;++i)
            for(int j=1;j<=n + m;++j)
                p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + a[i][j];


        for(int i=1;i<=n + m; ++i)
            for(int j=1;j<=n + m; ++j)if(a[i][j] == 1){
                ans[0]++;
                for(int d=1;d <= n + m - 2; ++d)
                    ans[d] += sum(max(1, i - d), max(1, j - d), min(n + m, i + d), min(n + m, j + d));
            }

        for(int i=n + m - 2; i>=1;--i)
            ans[i] = (ans[i] - ans[i - 1])/2;

        for(int i=1;i<=n+ m - 2;++i)
            cout<<ans[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
