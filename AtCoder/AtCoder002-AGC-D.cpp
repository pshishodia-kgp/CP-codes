/* 
  Use parallel binary search 
  Time Complexity : (M + Q)*LogM
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
int p[N], size[N], n, m, q, x[N], y[N], z[N], low[N], high[N];
vector<pair<int, int> > edge; 

void init(){
    for(int i=0;i<N;++i)p[i] = i, size[i] = 1; 
}

int root(int x){
    if(x != p[x])
        p[x] = root(p[x]); 
    return p[x]; 
}

void merge(int x, int y){
    x = root(x), y = root(y); 
    if(x == y)return ; 
    if(size[x] < size[y])swap(x, y); 
    p[y] = x; size[x] += size[y]; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n>>m;
    for(int i=0;i<m;++i){
        int x, y; cin>>x>>y; 
        edge.push_back({x, y}); 
    }
    cin>>q; 
    for(int i=0;i<q; ++i){
        cin>>x[i]>>y[i]>>z[i];
        high[i] = m - 1; low[i] = -1; 
    }

    while(1){
        vector<int> check[m]; 
        bool end = true;  
        for(int i=0;i<q;++i)if(high[i] - low[i] > 1){
            end = false;
            int mid = (low[i] + high[i])/2;
            check[mid].push_back(i);
        }
        if(end)break;

        init(); 
        for(int i=0;i<m;++i){
            merge(edge[i].first, edge[i].second); 

            for(int id : check[i]){
                int val; 
                if(root(x[id]) != root(y[id]))val = size[root(x[id])] + size[root(y[id])]; 
                else val = size[root(x[id])]; 

                (val >= z[id])? high[id] = i : low[id] = i; 
            }
        }
    }
    for(int i=0;i<q;++i)cout<<high[i] + 1<<"\n";
    return 0;
}
