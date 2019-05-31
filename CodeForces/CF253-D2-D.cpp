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

const int N = 405; 
int n, m, cost, sum[N][N]; 
string s[N]; 
vector<int> v[26][N][N]; 

inline int get_sum(int a, int b, int c, int d){
	return sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1]; 
}

//hola3

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ifstream input; ofstream output; 
    input.open("input.txt"); 
    output.open("output.txt"); 

	input>>n>>m>>cost; 
	for(int i=1;i<=n;++i){
		input>>s[i]; s[i] = '*' + s[i]; 
		for(int j=1;j<=m;++j){
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (s[i][j] == 'a'); 
			for(int k=j + 1;k <=m;++k)if(s[i][j] == s[i][k])
				v[s[i][j] - 'a'][j][k].push_back(i); 
		}
	}
	ll ans = 0; 
	for(int curr = 0; curr < 26;++curr)
		for(int i=1;i<=m;++i)
			for(int j=i + 1;j<=m;++j){
				vector<int> now = v[curr][i][j]; 
				int sz = now.size(); 
				for(int l = 0, r = 0; l < sz; ++l){
					r = max(l + 1, r); 
					while(r < sz && get_sum(now[l], i, now[r], j) <= cost)r++; 
					r--; 
					ans += r - l;
				}
			}
	output<<ans<<"\n"; 

    return 0;
}
