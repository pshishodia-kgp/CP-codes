/* 
dp[i][j] = Maximum total value by putting first i cakes in k boxes. 
Now, dp[i][j] = max{j <= i} ( dp[j - 1][k -1] + distinct_cakes_in [j, i] ) 
Suppose we store the values on right in another array now when i is changed to i + 1. There is only one transition possible of adding 1 to a range, 
that can be handled with lazy propagation. 
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define cerr cout
#define sz(a) (int)((a).size())
#define all(x) (x).begin(), (x).end()
string to_string(string s) { return '"' + s + '"';}
string to_string(char s) { return string(1, s);}
string to_string(const char* s) { return to_string((string) s);}
string to_string(bool b) { return (b ? "true" : "false");}
template <typename A> string to_string(A);
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A> string to_string(A v) {bool f = 1; string r = "{"; for (const auto &x : v) {if (!f)r += ", "; f = 0; r += to_string(x);} return r + "}";}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {cerr << " " << to_string(H); debug_out(T...);}
#define pr(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

// defines end

const int N = 35005;
int n,k,  a[N], prevId[N], dp[N][55]; 

struct Segment{
    int t[4*N], lazy[4*N];

    Segment(){
        fill(t, t + 4*N, 0); fill(lazy, lazy + 4*N, 0); 
    }

    void push(int node, bool leaf){
        t[node] += lazy[node]; 
        if(!leaf){
            lazy[2*node] += lazy[node]; 
            lazy[2*node + 1] += lazy[node];
        }
        lazy[node] = 0; 
    }

    void update(int node, int start, int end, int l, int r, int val){
        push(node, start == end); 
        if(start > r || end < l)return ; 
        if(start >= l && end <= r){
            lazy[node] += val; 
            push(node, start == end); return ; 
        }
        int mid = (start +end)/2;
        update(2*node, start, mid, l, r, val);
        update(2*node + 1, mid + 1, end, l, r, val); 
        t[node] = max(t[2*node], t[2*node + 1]); 
    }

    int query(int node, int start, int end, int l, int r){
        push(node, start == end); 
        if(start > r || end < l)return 0; 
        if(start >= l && end <= r)return t[node]; 

        int mid = (start + end)/2;
        int p1 = query(2*node, start, mid, l, r); 
        int p2 = query(2*node + 1, mid + 1, end, l, r); 
        return max(p1, p2); 
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>k;
    map<int, int> m;
    for(int i=1;i<=n;++i){
        cin>>a[i]; 
        prevId[i] = m[a[i]]; 
        m[a[i]] = i; 
    }

    for(int j=1;j<=k;++j){
        Segment tree; 
        for(int i=j;i<=n;++i){
            tree.update(1, 1, n, max(prevId[i] + 1, j) , i, 1); 
            tree.update(1, 1, n, i, i, dp[i - 1][j - 1]); 
            dp[i][j] = tree.query(1, 1, n, 1, i); 
        }
    }
    cout<<dp[n][k]<<"\n";
    return 0;
}
