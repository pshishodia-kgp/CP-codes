/*
 Notice that, we can binary search on the length of subsequence. 
 
 To check if a subsequence with length len is possible, suppose it has two types of counts x, and x + 1, then we will have x + 1 = ceil(len/8)
 Now we can check all permutations of [8] to see if it satisfies the condition. We can use bitmask to denote if a digit will appear x or x + 1 times. 
 
 
 and dp[d][i][len] = j, j is smallest index such that [i, j] contain len occurences of d.

 Time Complexity : O(8*n^2 + 8! * 2^8 * 8 ) = 8*10^7 operations.
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
int n, last[8][N][N], a[N]; 

bool F(int len){
    int x = (len + 7)/8 - 1;
    int num = 8*x + 8 - len;
    
    for(int mask = 0; mask < 256; ++mask)if(__builtin_popcount(mask) == num){
        vector<int> id = {0, 1, 2, 3, 4, 5, 6, 7};
        do{
            int idx = 0; 
            for(int d : id){
                if(mask & (1<<d)){
                    if(x == 0)continue;
                    idx = last[d][idx][x];
                }
                else idx = last[d][idx][x + 1];
            }
            if(idx < n){
                return true;
            }
        }
        while(next_permutation(id.begin(), id.end()));
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=0;i<n;++i){
        cin>>a[i]; a[i]--;
    }


    for(int d=0;d<8;++d){
        for(int len=1;len <=n;++len){
            last[d][n][len] = n;
            for(int i=n-1;i>=0;--i){
                last[d][i][0] = i;

                if(a[i] != d)last[d][i][len] = last[d][i + 1][len];
                else{
                    if(len == 1)last[d][i][len] = i; 
                    else last[d][i][len] = last[d][i + 1][len - 1];
                }
            }
        }
    }

    int low = 1, high = n + 1;
    while(high - low > 1){
        int mid = (low + high)/2;
        F(mid)? low = mid :  high = mid;
    }
    cout<<low<<"\n";

    return 0;
}
