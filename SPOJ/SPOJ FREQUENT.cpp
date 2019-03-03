/*
  Since, array elements are in range (-10^5, 10^5), and the array is increasing, You can store cnt for each element in a segment tree. 
  Now each query is max query in range (a[l] + 1, a[r] - 1), a[l], and a[r] can be handled separately.
  
  Note : If the constraints on a[i] were high, segment tree could be built over range [1, n] with each node storing cnt for prefix, suffix and maximum cnt
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
int n, t[4*N], a[N], cnt[N], startPos[N], endPos[N];

void update(int node, int start, int end, int id, int val){
    if(start > id || end < id)return ;
    if(start == end){
        t[node] = val;
        return ;
    }

    int mid = (start + end)/2;
    update(2*node, start, mid, id, val);
    update(2*node + 1, mid + 1, end, id, val);

    t[node] = max(t[2*node], t[2*node + 1]);
}

int query(int node, int start, int end, int l, int r){
    if(l > r)return 0;

    if(start > r || end < l)return 0;
    if(start >= l && end <= r){
        return t[node];
    }

    int mid = (start + end)/2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node + 1, mid + 1, end, l, r);

    return max(p1, p2);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(1){
        int n, q; cin>>n; if(n == 0)return 0;
        cin>>q;
        for(int i=0;i<4*N;++i)t[i] = 0;
        for(int i=0;i<N;++i)startPos[i] = endPos[i] = cnt[i] = 0;

        for(int i=1;i<=n;++i){
            cin>>a[i]; a[i] += 100000;
            if(startPos[a[i]] == 0)startPos[a[i]] = i;
            endPos[a[i]] = i;
            cnt[a[i]]++;
        }

        for(int i=0;i<N;++i)if(cnt[i]){
            update(1, 0, N - 1, i, cnt[i]);
        }

        while(q--){
            int l, r; cin>>l>>r;
            int left = a[l], right = a[r];

            int p = query(1, 0, N - 1, left + 1, right - 1);
            int p1 = min(r, endPos[left]) - l + 1;
            int p2 = r - max(startPos[right], l) + 1;

            cout<<max(max(p1, p2), p)<<"\n";
        }
    }
    return 0;
}
