/*
  queries can be handled by binary search and keeping lazy segment tree, by storing value of first element in each node. 
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
int n, t[4*N], a[N], prefix[N], pprefix[N], lazy[4*N], first[4*N]; 

void build(int node, int start, int end){
	if(start == end){
		t[node] = first[node] = a[start]; return;
	}
	int mid = (start + end)/2; 
	build(2*node, start, mid); 
	build(2*node + 1, mid + 1, end); 
	t[node] = t[2*node] + t[2*node + 1]; 
}

void push(int node, int start, int mid, int end){
	if(!lazy[node])return ; 
	t[node] = (end - start + 1)*first[node] + (pprefix[end - 1] - pprefix[start -1]) - (end - start)*prefix[start - 1]; 
	if(start != end){
		first[2*node] = first[node]; lazy[2*node] = 1; 
		first[2*node + 1] = first[node] + prefix[mid] - prefix[start - 1]; lazy[2*node + 1] = 1; 
	}
	lazy[node] = 0; 
}

void update(int node, int start, int end, int l, int r, int id, int val){
	int mid = (start + end)/2; 
	push(node, start, mid, end); 
	if(start > r || end < l)return ; 
	if(start >= l && end <= r){
		first[node] = val + prefix[start - 1] - prefix[id - 1]; lazy[node] = 1; 
		push(node, start, mid, end); return ; 
	}
	update(2*node, start, mid, l, r, id, val); 
	update(2*node + 1, mid + 1, end, l, r, id, val); 
	t[node] = t[2*node] + t[2*node + 1]; 
}

int get(int node, int start, int end, int l, int r){
	int mid = (start + end)/2; 
	push(node, start, mid, end); 
	if(start > r || end < l)return 0; 
	if(start >= l && end <= r)return t[node]; 
	return get(2*node, start, mid, l, r) + get(2*node + 1, mid + 1, end, l, r); 
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	cin>>n; 
	for(int i=1;i<=n;++i)cin>>a[i]; 
	for(int i=1;i<=n-1;++i){
		int k; cin>>k; 
		prefix[i] = prefix[i - 1] + k; 
		pprefix[i] = pprefix[i - 1] + prefix[i]; 
	}
	build(1, 1, n); 
	int q; cin>>q; 
	while(q--){
		char c; cin>>c; 
		if(c == '+'){
			int i, x; cin>>i>>x; 
			int low = i, high = n + 1; 
			int curr = get(1, 1, n, i, i); 
			while(high - low > 1){
				int mid = (low + high)/2;
				if(get(1, 1, n, mid, mid) < curr + x + prefix[mid - 1] - prefix[i - 1])low = mid; 
				else high =mid; 
			}
			update(1, 1, n, i, low, i, curr + x); 
		}
		else{
			int l, r; cin>>l>>r; 
			cout<<get(1, 1, n, l, r)<<"\n"; 
		}
	}

    return 0;
}
