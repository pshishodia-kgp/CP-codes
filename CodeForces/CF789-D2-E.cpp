/*
  https://codeforces.com/blog/entry/51250?#comment-351865
*/ 
#include <bits/stdc++.h>

using namespace std;

const int N = 2005, INF = 1e9;
int n, k, d[N];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>k;

    set<int> s; 
    for(int i=0;i<k;++i){
        int x; cin>>x; 
        s.insert(x);
    }
    vector<int> v;
    for(int x : s)v.push_back(x - n);

    for(int i=0;i<N;++i)d[i] = INF;

    d[1000] = 0;
    queue<int> q; q.push(1000);
    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(int x : v){
            if(curr + x == 1000){
                cout<<d[curr] + 1<<"\n"; return 0;
            }

            if(curr + x >= 0 && curr + x <= 2000 && d[curr] + 1 < d[curr + x]){
                d[curr + x] = d[curr] + 1;
                q.push(curr + x);
            }
        }
    }
    cout<<"-1\n";
    return 0;
}
