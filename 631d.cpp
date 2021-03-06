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

//#define TRACE

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

int n,m;
vector< pair<char, LL> > a,b;
int nfa[200005];

void build_NFA(){
    int x = 0;
    for(int i=1;i<=m;i++){
        nfa[i] = x;
        while(i!=m){
            if(x==0 and b[i].F==b[x].F and b[i].S>=b[x].S){
                x++;
                break;
            }
            if(x>0 and b[i].F==b[x].F and b[i].S==b[x].S){
                x++;
                break;
            }
            if(!x) break;
            x = nfa[x];
        }
    }
}

int kmp_search(int start){ 
    int cnt = 0;
    for(int i=start,x=0;i<SZ(a);){
        if(x<m and a[i].F==b[x].F and x==m-1 and a[i].S>=b[x].S) x++,i++;
        else if(x<m and a[i].F==b[x].F and x==0 and a[i].S>=b[x].S) x++,i++;
        else if(x<m and a[i].F==b[x].F and x>0 and x<m-1 and a[i].S==b[x].S) x++,i++;
        else if(!x) i++;
        else{
            int tp = nfa[x];
            if(tp-1==0 and a[i-1].S>=b[tp-1].S) x = nfa[x];
            else if(tp-1>0 and a[i-1].S==b[tp-1].S) x = nfa[x];
            else x = 0;
        }
        if(x==SZ(b)){cnt++;}
    }
    return cnt; 
}

int main(){
    si(n);si(m);
    for(int i=0;i<n;i++){
        int cnt;
        char tp[2];
        scanf("%lld-%s",&cnt,tp);
        if(!a.empty())
            if(a.back().F == tp[0]){
                a.back().S += cnt;
                continue;
            }
        a.PB(MP(tp[0],cnt));
    }
    for(int i=0;i<m;i++){
        int cnt;
        char tp[2];
        scanf("%lld-%s",&cnt,tp);
        if(!b.empty())
            if(b.back().F == tp[0]){
                b.back().S += cnt;
                continue;
            }
        b.PB(MP(tp[0],cnt));
    }
    n = SZ(a);
    m = SZ(b);
    if(SZ(b)==1){
        LL ans = 0;
        for(int i=0;i<n;i++){
            if(a[i].F==b[0].F and a[i].S>=b[0].S) ans += (LL)a[i].S-(LL)b[0].S+1LL;
        }
        lldout(ans);
        return 0;
    }
    build_NFA();      
    int ans = kmp_search(0);
    dout(ans);
    return 0;
}
