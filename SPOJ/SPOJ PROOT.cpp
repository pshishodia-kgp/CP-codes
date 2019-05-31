/*
Check if for all x = (p - 1)/q where q is a prime  divisor of p, r^x gives 1 modulo p. 
*/
#include <bits/stdc++.h>

using namespace std;

int MOD; 

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



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	while(1){
		int p, n; cin>>p>>n;
		if(p == 0 && n == 0)return 0; 
		MOD = p;
		vector<int> v; int x = p - 1; 
		for(int i = 2;1ll*i*i <= x; ++i)if(x%i == 0){
			v.push_back((p - 1)/i); 
			while(x%i == 0)x /= i; 
		}
		if(x > 1)v.push_back((p - 1)/x); 

		while(n--){
			int r; cin>>r; 
			r%= MOD; 
			bool check = true;
			if(r == 0)check = false;  
			for(int d : v)if(binpow(r, d) == 1)check = false; 
			check? cout<<"YES\n" : cout<<"NO\n"; 
		}
	}	

    return 0;
}
