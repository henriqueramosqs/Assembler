#include <bits/stdc++.h>
#include "instructionSet.cpp"
#define dbg(x) cout<<#x<<": "<<x<<"\n";
#define rep(i,a,b) for(int i = a;i<b;i++)
#define pb push_back
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
    map<string,int> symbolsTable;
    
    Program(InputFile input){
        
        vector<string> strings =split(input.getRaw());

        cout<<"\n\n\nSPLITTED\n";
        for(auto c:strings){
            cout<<c<<" ";
        }cout<<"\n";

        int sz = strings.size();
        int curAddress=0;
        int l = 0; 
        while(l<sz){
            // enquanto eu não encontrar um rótulo ou uma operação,
            // estou olhando para argumentos da operação atual

            int r = l+1;
            while(r<sz){
                if(!isKnownOperand(strings[r]) && strings[r].back()!=':'){
                    r++;
                }else{
                   break;
                }
            }

            cout<<"\nlidando com trecho\n";
            rep(i,l,r)cout<<strings[i]<<"\n";
            cout<<"\n";

            if(strings[l].back()==':'){    
                strings[l].pop_back();
                try{    
                    validateArg(strings[l]);
                }catch(const char * excpt){
                    cout<<excpt;
                    l=r;
                    continue;
                }

                if(strings[l+1]=="CONST"){
                    //arrumar depois
                    if(r-l !=3){
                        cerr<<"Sintaxe inválida !";
                    }else if(symbolsTable.find(strings[l])!=symbolsTable.end()){
                        cerr<<"Símbolo"<<strings[l]<<"já definido\n";
                    }else{
                        symbolsTable[strings[l]]=stoi(strings[l+2]);
                    }
                }else if(strings[l+1]=="SPACE"){
                    symbolsTable[strings[l]]=0;
                }else{
                    symbolsTable[strings[l]]=curAddress;
                }
                l=r;
                continue;
            }

            vector<string> aux(strings.begin()+l,strings.begin()+r);
            try{
                instructions.pb(getInstruction(aux));
                instructions.back().setAddress(curAddress);
                curAddress+=instructions.back().getSize();
            }catch(const char *expt){
                cout<<expt<<"\n";
            }
            l=r;
        }   
        
        cout<<"\n\ninstructions:\n\n";
        for(auto c:instructions)cout<<c<<"\n";
    }   
    
    vector<int> secondPass(){
        vector<int>mem;
        for(auto c:instructions){
            bool qt = false;
            for(auto x:c.getArgs()){
                if(symbolsTable.find(x)==symbolsTable.end()){
                    cerr<<"Símbolo "<<x<<" nunca foi definido"<<"\n";
                    qt = true;
                }       
            }


            if(qt)continue;

            mem.pb(c.getOpcode());
            for(auto x:c.getArgs()){
                mem.pb(symbolsTable[x]);
            }

        }

        return mem; 
    }
};

int main(){
    InputFile input;
    input.readFile()->cleanText();

    cout<<input.getRaw();

    Program pr(input);

    for(auto x: pr.secondPass()){
        cout<<x<<"\n";
    };

}   

