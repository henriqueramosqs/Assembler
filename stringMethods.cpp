#include <bits/stdc++.h>
#define dbg(x) cout<<#x<<": "<<x<<"\n";
#define rep(i,a,b) for(int i = a;i<b;i++)
#define pb push_back
using namespace std;


string trim(string s){
    int n = s.size(); 
    string ans="";
    rep(i,0,n){
        if(s[i]=='\n' || s[i]=='\t' || s[i]==','){
            s[i]=' ';
        }
        if(s[i]!=' ' || (!ans.empty() && ans.back()!=' ')){
            ans+=s[i];
        }
    }
    return ans;
}

vector<string>split(string s){
    vector<string>ans;
    string cur="";
    for(auto c:s){
       if(c==' ' && !cur.empty()){
            if(cur!="SECAO" && cur!="TEXT" && cur!="DATA")ans.pb(cur);
            cur="";
       }else{
        cur+=c;
       }
    }
    if(!cur.empty() && cur!="SECAO" && cur!="TEXT" && cur!="DATA")ans.pb(cur);
    return ans;
}

bool isLetter(char a){
   return (a>='a' && a<='z') || (a>='A' && a<='Z');
}

bool isNumber(char a){
    return (a>='0' && a<='9');
}
