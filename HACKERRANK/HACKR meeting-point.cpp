/* 
Rotate the grid by 45 degrees to convert max{|x1 - x2, |y1 - y2|} to mahantann distance 
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;
#define int ll
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
int ans[N];     

void compute(vector<pair<int, int> > &v){
    int n = v.size();
    vector<int> prefix(n); 
    prefix[0] = v[0].first; 
    for(int i=1;i<n;++i)prefix[i] = prefix[i - 1] + v[i].first; 

    for(int i=0;i<n;++i){
        ans[v[i].second] += (2*(i + 1) - n)*v[i].first + prefix[n - 1] - 2*prefix[i]; 
    }
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin>>n;
    vector<pair<int, int> > a(n), b(n); 
    for(int i=0;i<n;++i){
        int x, y; cin>>x>>y; 
        a[i] = {x - y, i}; 
        b[i] = {x + y, i}; 
    }
    sort(all(a)); sort(all(b)); 
    compute(a); compute(b); 

    int mn = ans[0]; 
    for(int i=0;i<n;++i)mn = min(mn, ans[i]); 
    cout<<mn/2<<"\n"; 
    return 0;
}
