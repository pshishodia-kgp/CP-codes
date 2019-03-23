/* Divide 14 strings into two sets, for each preprocess the matching positions using KMP. Now for each of the 7! permutations
of both groups store the minimum position it can occur in that order from start and end. 

Now use two pointers, to find ans
Time Complexity : O(n + mC(m/2) * (m/2)! *  m)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll; 

const int N = 1e5 + 5, M = 16;
int n, m, mlast[M][N], mfirst[M][N];
vector<int> v1[1024*16 + 5], v2[1024*16 + 5];
string p[M], s;

void process(int id){
    int sz = (int)p[id].size();

    vector<int> pi(sz);
    for(int i=0;i<n;++i)
        mlast[id][i] = n, mfirst[id][i] = -1;

    // prefix automaton

    int j = 0;
    for(int i=1;i<sz;++i){
        while(j > 0 && p[id][j] != p[id][i])j = pi[j - 1];

        if(p[id][i] == p[id][j])j++;
        pi[i] = j;
    }

    j = 0;
    for(int i=0;i<(int)s.size();++i){
        while(j > 0 && p[id][j] != s[i])j = pi[j - 1];

        if(p[id][j] == s[i])j++;

        if(j == sz){
            mlast[id][i - sz + 1] = i;
            mfirst[id][i] = i - sz + 1;
        }
    }

    // information stored

    for(int i=n-2;i>=0;--i)
        mlast[id][i] = min(mlast[id][i], mlast[id][i + 1]);

    for(int i=1;i<n;++i)
        mfirst[id][i] = max(mfirst[id][i], mfirst[id][i - 1]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    cin>>n>>m;
    cin>>s;
    for(int i=0;i<m;++i)cin>>p[i];

    int totalSize = 0;
    for(int i=0;i<m;++i)totalSize += (int)p[i].size();

    if(totalSize > n){
        cout<<"0\n"; return 0;
    }

    for(int i=0;i<m;++i)
        process(i); 

    int half1 = m/2, half2 = (m + 1)/2;
    for(int mask = 0; mask < (1<<m); ++ mask )if(__builtin_popcount(mask) == half1 || __builtin_popcount(mask) == half2){
        vector<int> id;
        for(int i=0;i<m;++i)if(mask & (1<<i))
            id.push_back(i);

        do{
            int fst = n, lst = -1;
            for(int i=0;i<id.size();++i){
                if(lst >= n - 1)lst = n;
                else lst = mlast[id[i]][lst + 1];

                if(fst <= 0)fst = -1;
                else fst = mfirst[id[i]][fst - 1];
            }
                // cout<<"mask fst lst "<<mask<<" "<<fst<<" "<<lst<<"\n";

            if(lst < n)v1[mask].push_back(lst);
            if(fst >= 0)v2[mask].push_back(fst);
        }while(next_permutation(id.begin(), id.end()));

        sort(v1[mask].begin(), v1[mask].end());
        sort(v2[mask].begin(), v2[mask].end());
    }

    long long ans = 0;
    for(int mask = 0;mask < (1<<m); ++mask)if(__builtin_popcount(mask) == half1){
        int neg = (1<<m) - 1 - mask;

        for(int i=0, j = 0;i < v1[mask].size();++i){
            while(j < v2[neg].size() && v1[mask][i] >= v2[neg][j])j++;

            if(j == v2[neg].size())break;

            ans += (int)v2[neg].size() - j;
        }
    }

    cout<<ans<<"\n";
}
