//joyneel
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI > 	VVI;
typedef long long int 	LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);

const LL INF = 1e17;
LL d[100005];
VII g[100005];
int p[100005];
int vs[100005];

int main(){
  int n,m;
  cin>>n>>m;
  for(int i=0;i<m;i++){
    int a,b,c;
    cin>>a>>b>>c;
    g[a].PB(MP(b,c));
    g[b].PB(MP(a,c));
  }
  set<pair<LL,int>> s;
  for(int i=1;i<=n;i++) d[i] = INF;
  d[1] = 0;
  s.insert(MP(d[1],1));
  while(!s.empty()){
    int u = s.begin()->S;
    s.erase(s.begin());
    vs[u] = 1;
    for(int i=0;i<SZ(g[u]);i++){
      int w = g[u][i].F;
      LL edge = g[u][i].S;
      if(vs[w]) continue;
      if(d[w] > d[u] + edge){
        p[w] = u;
        if(s.find(MP(d[w],w))!=s.end()) s.erase(s.find(MP(d[w],w)));
        d[w] = d[u] + edge;
        s.insert(MP(d[w],w));
      }
    }
  }
  if(!vs[n]) cout<<-1<<endl;
  else{
    VI v;
    int u = n;
    while(u!=1){
      v.PB(u);
      u = p[u];
    }
    v.PB(1);
    reverse(ALL(v));
    for(int i=0;i<SZ(v);i++) cout<<v[i]<<' '; cout<<endl;
  }
  return 0;
}
