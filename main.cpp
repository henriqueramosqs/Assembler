#include <bits/stdc++.h>
#include "instructionSet.cpp"
#define dbg(x) cout<<#x<<": "<<x<<"\n";
using namespace std;

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
        string ans="";
        
        for(char c: rawText){
            
            if(c==' '){
                if(!ans.empty() && ans.back()!=' '
                    && ans.back() !='\n' && ans.back()!=',')ans+=c;
                continue;
            }

            if(c=='\n'){
               if(!ans.empty() && ans.back() !='\n')ans+=c;
                continue;
            }

            ans+=c; 
            
        }
        rawText=ans;
    }

    string getRaw(){
        return rawText;
    }
    
};

vector<string>split(string s){
    vector<string>ans;
    string cur="";
    for(auto c:s){
        if(c==',' || c==' ' || c=='\n'){
            ans.push_back(cur);
        }else{
            cur+=c;
        }
    }
    return ans;
}
class Program{
public:
    vector<Instruction> instructions;
    // tabela de símbolos
    Program(InputFile input){
        string cur="";
        for(auto c:input.getRaw()){
            //processa intrução que está sendo formada
            cur+=c;

            if(c=='\n'){    
                vector<string> instructionInfo = split(cur);
                instructions.push_back(*getInstruction(instructionInfo));
                cur="";
            }
        }
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