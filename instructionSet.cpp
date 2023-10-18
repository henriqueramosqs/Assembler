#include <bits/stdc++.h>
#include "stringMethods.cpp"
#define dbg(x) cout<<#x<<": "<<x<<"\n";
#define rep(i,a,b) for(int i = a;i<b;i++)
using namespace std;
string operations[14]={"ADD","SUB","MUL","DIV","JMP","JMPN","JMPP","JMPZ","COPY","LOAD","STORE","INPUT","OUTPUT","STOP"};

// Checks if operation is valid
bool isKnownOperation(string s){
   rep(i,0,14){
    if(operations[i]==s)return true;
   }
   return false;
}


// Checks if label is valid. If not, throws Exception
void validateArg(string s){
    if(isNumber(s[0])){
        throw "Valid operands must not start with a number";
    }
    for(auto c:s){
        if(!isLetter(c) && !isNumber(c) && c!='_' && c!='+'){
            throw "Valid operands might only contain english alphabet letters, numbers and _";
        }
    }

}


// Instruction class
class Instruction{
private:
    string mnemonic;
    short opcode;
    short size;
    int address;
    vector<string>args;

public:
    Instruction(string mnemonic, short opcode,short size,vector<string>args){
        this->mnemonic = mnemonic;
        this->opcode = opcode;
        this->size =size;
        this->args=args;
    }

    string getMnemonic(){
        return mnemonic;
    }

    short getOpcode(){
        return opcode;
    }

    short getSize(){
        return size;
    }

    int getAddress(){
        return address;
    }

    vector<string> getArgs(){
        return args;
    }

    // Inserts argument into arguments. If not valid prints exception
    void insertArg(string x){
        try{
            validateArg(x);
            args.push_back(x);
        }catch(const char *expt){
            cout<<"Syntax error in argument "<<x<<" "<<expt<<"\n";
        }
       
    }
    void setAddress(int x){
        address=x;
    }

};



// returns char array for wrong operands quantity
const char *InvalidArgumentQtd(const string operation, int expected, int provided) {
    string message = "Semantic Error! Operation " + operation + " demands " +
                to_string(expected) + " arguments, whereas " +
                to_string(provided) + " were provided!";
    return message.c_str();
            
}



// Assembles intructino
Instruction getInstruction(vector<string> a){
    string operation = a[0];

    if (operation == "ADD") {

       if(a.size()!=2){
            throw InvalidArgumentQtd("ADD",1,a.size()-1);
       }
       a.erase(a.begin());
       return Instruction(operation,1,2,a);

    } else if (operation == "SUB") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("SUB",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,2,2,a);

    } else if (operation == "MUL") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("MUL",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,3,2,a);

    } else if (operation == "DIV") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("DIV",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,4,2,a);   
          
    } else if (operation == "JMP") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("JMP",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,5,2,a);   

    } else if (operation == "JMPN") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("JMPN",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,6,2,a);   

    } else if (operation == "JMPP") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("JMPP",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,7,2,a);   

    } else if (operation == "JMPZ") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("JMPZ",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,8,2,a);   

    } else if (operation == "COPY") {
        
        if(a.size()!=3){
            throw InvalidArgumentQtd("COPY",2,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,9,3,a);   

    } else if (operation == "LOAD") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("LOAD",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,10,2,a);   

    } else if (operation == "STORE") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("STORE",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,11,2,a);  


    } else if (operation == "INPUT") {
        
        if(a.size()!=2){
            throw InvalidArgumentQtd("INPUT",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,12,2,a);  
    
    } else if (operation == "OUTPUT") {

        if(a.size()!=2){
            throw InvalidArgumentQtd("OUTPUT",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,13,2,a);  


    } else if (operation == "STOP") {

        if(a.size()!=1  ){
            throw InvalidArgumentQtd("STOP",0,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,14,1,a);  

    } else {
        cerr<<"Operação desconhedida\n";
    }

}

ostream &operator<<(std::ostream &os, Instruction &a) { 
    string args="";
    for(auto c:a.getArgs())args+=(c+" ");
    return (os <<a.getAddress()<<": "<<a.getMnemonic()<<" ("<<a.getOpcode()<<") - sz: "<<a.getSize()<<"\n"<<"args: "<<args<<"\n\n");

}



