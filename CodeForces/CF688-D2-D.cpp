/*
k must divide lcm of numbers otherwise for each remainder modulo k there will exist solution, by chinese remainder theorem.
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k; cin>>n>>k;
    vector<int> c(n);

    for(int i=0;i<n;++i)cin>>c[i];

    bool check = true;

    for(int i=2;i<= k;++i)if(k%i == 0){
        int pw = 1;
        while(k %i == 0){
            k /= i; pw *= i;
        }

        bool check1 = false;
        for(int i=0;i<n;++i)if(c[i]%pw == 0)check1 = true;

        if(!check1)check = false;
    }

    if(check)cout<<"Yes\n";
    else cout<<"No\n";

    return 0;
}
