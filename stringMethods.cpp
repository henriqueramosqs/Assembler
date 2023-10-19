#include <bits/stdc++.h>
#define dbg(x) cout<<#x<<": "<<x<<"\n";
#define rep(i,a,b) for(int i = a;i<b;i++)
#define pb push_back
using namespace std;


bool isLetter(char a){
   return (a>='a' && a<='z') || (a>='A' && a<='Z');
}

bool isNumber(char a){
    return (a>='0' && a<='9');
}

string toUpper(string s){
    string ans="";
    for(auto c:s){
        if(!isLetter(c)){
            ans+=c;
        }else{
            if(c>='a' && c<='z'){
                ans+=(c+'A'-'a');
            }else{  
                ans+=c;
            }
        }
    }
    return ans;
}



vector<string>split(string s){
    vector<string>ans;
    string cur="";

    for(auto c:s){
       if(c==' ' && !cur.empty()){
            ans.pb(toUpper(cur));
            cur="";
       }else{
        cur+=c;
       }
    }
    if(!cur.empty())ans.pb(toUpper(cur));
    return ans;
}




string trim(string s){
    int n = s.size(); 
    string ans="";

    bool isSummign = false;
    bool isWritingNumber=false;

    rep(i,0,n){
        if(isNumber(s[i]))isWritingNumber=true;

        if(s[i]=='+'){
            if(!ans.empty() && ans.back()==' ')ans.pop_back();
            isSummign=true;
        }
        if(s[i]=='\n' || s[i]=='\t' || s[i]==','){
            if(isWritingNumber){
                isWritingNumber=false;
                isSummign=false;
            }
            s[i]=' ';
        }
        if(s[i]!=' ' || (!ans.empty() && ans.back()!=' ' && !isSummign)){
            ans+=s[i];  
        }
    }
    return ans;
}
