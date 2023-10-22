#include <bits/stdc++.h>
#include "instructionSet.cpp"
#define dbg(x) cout<<#x<<": "<<x<<"\n";
#define rep(i,a,b) for(int i = a;i<b;i++)
#define pb push_back
using namespace std;
bool isMacroFile = false;
string objName;



string getObjName(string path){
    string ans="";
    int n= path.size();
    int l=0;

    rep(j,0,n){
        int _l = n-1-j;
        if(path[_l]=='/'){
            l=_l+1;
            break;
        }
    }
    string extension="";
    bool orgName = true;
    rep(i,l,n){
        if(path[i]=='.'){
            orgName=false;
        }
        if(!orgName)extension+=path[i];
        if(orgName)ans+=path[i];
    }
    if(extension==".mcr")isMacroFile = true;
    ans+=".obj";
    return ans;
}

class InputFile{
private:
    string rawText;

public:

    InputFile* readFile(ifstream &inputFile){
        string aux;
    
        while(getline(inputFile,aux)){
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
    vector<int>auxData;

    int curAddress=0;
    // tabela de símbolos
    map<string,pair<bool,int> > symbolsTable;
    // tabela de macros
    map<string,pair<int,vector<string> > >macros;


    bool isMacro(string x){
        return macros.find(x)!=macros.end();
    }


    void insertMacro(vector<string> v){
        string nome = v[0];
        v.erase(v.begin());
        map<string,int> args;
        int counter=0;


        vector<string>subs;


        for(auto &c:v){
            if(c=="MACRO" || c=="ENDMACRO")continue;

            if(c[0]=='&'){
                string nome = c.substr(1,c.size()-1);
                if(args.find(nome)!=args.end()){
                    c=('#'+to_string(args[nome]));
                }else{
                    args[nome]=counter++;
                    continue;
                }   
            }
            subs.pb(c);
            
        }
        macros[nome]=make_pair(counter,subs);
    }


    void showMacros(){
        cout<<"\nDefined Macros:\n";

        for(auto c:macros){
        cout<<c.first<<" ("<<c.second.first<<") ";
        for(auto x:c.second.second)cout<<x<<" ";
        cout<<"\n";
        }
    }


    void showSymbolsTable(){
        cout<<"\nSymbols Table\n";
        for(auto c:symbolsTable){
            cout<<c.first<<" ("<<c.second.first<<") "<<c.second.second<<"\n";
        }cout<<"\n";    
    }
    
    Program(InputFile input){
        
        vector<string> strings =split(input.getRaw());

        int sz = strings.size();


        string preArchive="";
        
        // stans for relative data
        int dataAddr=0;
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

                vector<string> aux1(strings.begin()+l,strings.begin()+r+1);
                strings.erase(strings.begin()+l,strings.begin()+r+1);
                strings.insert(strings.end(),aux1.begin(),aux1.end());
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


        cout<<"\n\nTreated input:\n";
        for(auto c:strings){
            cout<<c<<" ";
        }cout<<"\n";


        int l = 0; 
        // Uses two pointers technique to separate instructions
        while(l<strings.size()){

            // While I did not find an operator or label, I'm still looking
            // at operands of current instruction

            int r = l+1;
            while(r<strings.size()){
                if(!isKnownOperation(strings[r]) && !isMacro(strings[r]) && strings[r].back()!=':'){
                    r++;
                }else{
                   break;
                }
            }

            cout<<"\nlidando com trecho\n";
            rep(i,l,r)cout<<strings[i]<<" ";
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
                            symbolsTable[strings[l]]=make_pair(false,dataAddr);
                            auxData.pb(stoi(strings[l+2]));
                            dataAddr++;
                            rep(i,l,1)preArchive+=(strings[i]+" ");
                            preArchive+="\n";
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
                            auxData.pb(0);
                            symbolsTable[strings[l]]=make_pair(false,dataAddr);
                            dataAddr++;
                            
                            //pre
                            rep(i,l,r)preArchive+=(strings[i]+" ");
                            preArchive+="\n";
                        }else{
                            int qtd;
                            try{
                                qtd = stoi(strings[l+2]);

                                rep(i,l,r)preArchive+=(strings[i]+" ");
                                preArchive+="\n";

                            }catch(const char * expt){
                                 cerr<<"Not possible to convert "<<strings[l+2]<<" to integer";
                                 l=r;
                                 continue;
                            }
                            rep(i,0,qtd)auxData.pb(0);
                            symbolsTable[strings[l]]=make_pair(false,dataAddr);
                            dataAddr+=qtd;

    
                        }
                    }
                }else if(strings[l+1]=="MACRO"){
                    while(r<strings.size() && strings[r]!="ENDMACRO")r++;
                    r++;    
                    vector<string> aux_v(strings.begin()+l,strings.begin()+r);
                    insertMacro(aux_v);
                }else{
                    symbolsTable[strings[l]]=make_pair(true,curAddress);
                }
                l=r;
                continue;
            }


            if(isMacro(strings[l])){
            
                int argsCounter=r-l-1;
                if(argsCounter!=macros[strings[l]].first){
                    cerr<<"\nMACRO "<<strings[l]<<"has invalid amount of operands\n";
                    l=r;
                }else{
                    vector<string>substitute = macros[strings[l]].second;


                    rep(counter,0,argsCounter){
                        while(true){

                            auto it = find(substitute.begin(),substitute.end(),"#"+to_string(counter));
                            if(it==substitute.end())break;
                            *it = strings[l+1+counter];
                        }
                    }

                    auto stt = strings.begin()+l;
                    auto edd = strings.begin()+r;
                    strings.erase(stt,edd);
                    strings.insert(stt,substitute.begin(),substitute.end());
                }
                continue;
            }else{

                vector<string> aux(strings.begin()+l,strings.begin()+r);
                try{
                    instructions.pb(getInstruction(aux));
                    instructions.back().setAddress(curAddress);
                    curAddress+=instructions.back().getSize();
                    rep(i,l,r)preArchive+=(strings[i]+" ");
                    preArchive+="\n";
                }catch(const char *expt){
                    cout<<expt<<"\n";
                }
            }
            l=r;
        }   
        for(auto &c:symbolsTable){
            if(c.second.first==false){
                c.second.second +=curAddress;
            }
        }


        if(isMacroFile){
            ofstream macroFile(objName.substr(0,objName.size()-4) +".pre");
            macroFile<<preArchive;
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

    void secondPass(ofstream &out){
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
            out<<c.getOpcode()<<" ";

            for(auto x:treatedArgs){
                memory.pb(symbolsTable[x.first].second+x.second);
                out<<symbolsTable[x.first].second +x.second<<" ";
            }
        }

        for(auto c:auxData){
            memory.pb(c);
            out<<c<<" ";
        }


        for(auto x:memory ){
        cout<<x<<"\n";
        }
    }



};



int main(int argc, char* argv[]){



    if(argc!=2){
        cerr << "Please inform only the realative path to the desired file " << argv[1] << "\n";
        return 0;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << argv[1] << "\n";
        return 0;
    }

    objName = getObjName(string(argv[1]));
    ofstream outputFile(objName);

    InputFile input;

    input.readFile(inputFile)->cleanText();

    inputFile.close();

    cout<<input.getRaw();

    Program pr(input);
    pr.secondPass(outputFile);

    pr.showSymbolsTable();
    pr.showMacros();

    outputFile.close();
}   

