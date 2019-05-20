/*
Idea same as scott wu's comment, if m is even answer always exists which can be constructed by directig edgs such that indegree of each vertex is even, which is pretty standard
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

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
inline int add(int a, int b){a += b; if(a >= MOD)a -= MOD; return a;}
inline int sub(int a, int b){a -= b; if(a < 0)a += MOD; return a;}
inline int mul(int a, int b){return (int)((long long) a * b %MOD);}
inline int binpow(int a, int b){int res = 1; while(b > 0){ if(b & 1)res = mul(res, a); a = mul(a, a);b /= 2;} return res;}
inline int inv(int a){return binpow(a, MOD - 2);}
int gcd(int a, int b, int &x, int &y){if(a == 0){x = 0, y = 1; return b;} int x1, y1;  int d = gcd(b%a, a, x1, y1); x = y1 - (b/a) * x1; y = x1; return d;}

const int N = 1e5 + 5;
int n, m, vis[N], indeg[N], edge[N]; 
vector<pair<int, int> > g[N];
vector<int>  ans[N]; 

void dfs(int v, int prnt){
    vis[v] = 1; 
    for(auto p  : g[v]){
        int u = p.first, no = p.second; 
        if(u == prnt)continue;

        if(edge[no])continue; 
        if(!vis[u]){
            dfs(u, v); 
            if(indeg[u]%2 == 0){
                indeg[v]++; 
                ans[v].push_back(u); 
            }
            else ans[u].push_back(v);
            edge[no] = 1;  
        }else{
            edge[no] = 1; 
            indeg[v]++;
            ans[v].push_back(u); 
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>m;
    for(int i=0;i<m;++i){
        int x, y; cin>>x>>y; 
        g[x].push_back({y, i}); g[y].push_back({x, i}); 
    }
    if(m & 1){
        cout<<"No solution\n"; return 0;
    }
    dfs(1, 0);
    for(int i = 1; i<=n;++i){
        assert(ans[i].size()%2 == 0); 
        for(int j=0;j<ans[i].size();j += 2)
            cout<<ans[i][j]<<" "<<i<<" "<<ans[i][j + 1]<<"\n"; 
    }
    return 0;
}
