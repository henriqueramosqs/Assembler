#include <bits/stdc++.h>
#include "instructionSet.cpp"
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
            ans.pb(cur);
            cur="";
       }else{
        cur+=c;
       }
    }
    if(!cur.empty())ans.pb(cur);
    return ans;
}
class InputFile{
private:
    string rawText;

public:
    InputFile* readFile(){
        string aux;
    
        while(getline(cin,aux)){
            aux+='\n';
            rawText+=aux;
        }
        return this;
    }


    void rmComments(){
        string ans="";

        bool comment = false;
        for(auto c:rawText){
            if(comment){
                if(c=='\n'){
                    comment=false;
                }else{
                    continue;
                }
            }
            if(c==';'){
                comment = true;
                continue;
            }
            ans+=c;
        }

        rawText=ans;
    }
    // eliminates multiple spaces, EOL's and commentaries
    void cleanText(){
        rmComments();
        cout<<"No comments: ";
        cout<<getRaw()<<"\n";
        rawText = trim(rawText);
    }

    string getRaw(){
        return rawText;
    }
    
};

class Program{
public:
    vector<Instruction> instructions;
    // tabela de símbolos
    Program(InputFile input){
        vector<string> strings =split(input.getRaw());
        int sz = strings.size();
        int l = 0; 
        while(l<sz){
            // enquanto eu não encontrar um rótulo ou uma operação,
            // estou olhando para argumentos da operação atual

            int r = l+1;
            while(r<sz){
                if(!isKnownOperand(strings[r]) && !isLabel(strings[r])){
                    r++;
                }else{
                   break;
                }
            }
            
            vector<string> aux(strings.begin()+l,strings.begin()+r);
            instructions.pb(getInstruction(aux));
            l=r;
        }   
        
        cout<<"\ninstructions:";
        for(auto c:instructions)cout<<c<<"\n";
    }   
};

int main(){
    InputFile input;
    input.readFile()->cleanText();

    cout<<input.getRaw();

    Program pr(input);

    for(auto c:pr.instructions){
        cout<<c;
    }

}   