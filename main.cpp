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
    vector<int> memory;

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

        // if Data section if last, moves it to front
        bool dataFound=false;
        rep(l,0,sz){

            if(strings[l]=="DATA"){
                int r = sz-1;
                rep(_r,l+1,sz){
                    if(strings[_r]=="TEXT"){
                        r= _r;
                        break;
                    }
                }
                printf("l,r foun = %d,%d\n",l,r);

                vector<string> aux1(strings.begin()+l,strings.begin()+r+1);
                strings.erase(strings.begin()+l,strings.begin()+r+1);
                strings.insert(strings.begin(),aux1.begin(),aux1.end());
                break;

            }

        }


        for(auto it = strings.begin();it!=strings.end();){
            if(*it == "DATA" || *it =="SECAO" || *it=="TEXT"){
                strings.erase(it);
            }else{
                it++;
            }
        }
        cout<<"\n\nAfter Change\n";
        for(auto c:strings){
            cout<<c<<" ";
        }cout<<"\n";

        int l = 0; 
        sz= strings.size();
        // Uses two pointers technique to separate instructions
        while(l<sz){

            // While I did not find an operator or label, I'm still looking
            // at operands of current instruction

            int r = l+1;
            while(r<sz){
                if(!isKnownOperation(strings[r]) && strings[r].back()!=':'){
                    r++;
                }else{
                   break;
                }
            }

            cout<<"\nlidando com trecho\n";
            rep(i,l,r)cout<<strings[i]<<"\n";
            cout<<"\n";

            // If first string is a label
            if(strings[l].back()==':'){     
                strings[l].pop_back();

                // Checks if label is valid, if not, cuts intruction
                // ans jumps to next
                try{    
                    validateArg(strings[l]);
                }catch(const char * excpt){
                    cout<<excpt;
                    l=r;
                    continue;
                }

                if(strings[l+1]=="CONST"){

                    // If no const value is informed
                    if(r-l !=3){
                        cerr<<"Invalid syntax ! Const value not declaref";

                   
                    }else if(symbolsTable.find(strings[l])!=symbolsTable.end()){
                         // If label is already defined
                        cerr<<"Symbol"<<strings[l]<<"already defined\n";
                    }else{

                        // Makes assignment at symbols table
                        try{
                            symbolsTable[strings[l]]=curAddress;
                            memory.pb(stoi(strings[l+2]));
                            curAddress++;

                        }catch(char *excpt){
                            cerr<<"Not possible to convert "<<strings[l+2]<<" to integer";
                        }
                    }
                }else if(strings[l+1]=="SPACE"){
                    if(r-l>3){
                        cerr<<"Error in \"";
                        rep(aux,l,r)cerr<<strings[aux]<<" ";
                        cerr<<"\". Too Many arguments informed\n";
                        l=r;
                        continue;
                    }else{
                        if(r==l+2){
                            memory.pb(0);
                            symbolsTable[strings[l]]=curAddress;
                            curAddress++;
                        }else{
                            int qtd;
                            try{
                                qtd = stoi(strings[l+2]);
                            }catch(const char * expt){
                                 cerr<<"Not possible to convert "<<strings[l+2]<<" to integer";
                                 l=r;
                                 continue;
                            }
                            rep(i,0,qtd)memory.pb(0);
                            symbolsTable[strings[l]]=curAddress;
                            curAddress+=qtd;
                        }
                    }
                }else{
                    symbolsTable[strings[l]]=curAddress;
                    curAddress++;
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
        
    }   
    

    pair<string,int> solveOperand(string x){
        string ans="";
        string dif_st="";
        bool firstPart=true;

        for(auto c:x){
            if(c=='+'){
                firstPart=false;
                continue;
            }
            if(firstPart){
                ans+=c;
            }else{
                dif_st+=c;
            }
        }  
        int dif =0;
        if(!dif_st.empty()){
            dif = stoi(dif_st);
        }
        return make_pair(ans,dif);
    }

    void secondPass(){
        for(auto c:instructions){
            bool qt = false;

            vector<pair<string,int > >treatedArgs;

            for(auto x:c.getArgs()){
                pair<string,int> arg;
                try{
                    arg = solveOperand(x);
                }catch(...){
                    cerr<<"It was not possible to solve operand "<<x<<"\n";
                    qt=true;
                }
                if(symbolsTable.find(arg.first)==symbolsTable.end()){
                    cerr<<"Sybol "<<arg.first<<" was never defined"<<"\n";
                    qt = true;
                }else{
                    treatedArgs.push_back(arg);
                }
            }


            if(qt)continue;

            memory.pb(c.getOpcode());

            for(auto x:treatedArgs){
                memory.pb(symbolsTable[x.first]+x.second);
            }

        }

        for(auto x:memory ){
        cout<<x<<"\n";
        }
    }



};

int main(){

    InputFile input;
    input.readFile()->cleanText();

    cout<<input.getRaw();

    Program pr(input);
    pr.secondPass();
}   

