#include <bits/stdc++.h>
#define dbg(x) cout<<#x<<": "<<x<<"\n";
using namespace std;

class Instruction{
protected:
    string mnemonic;
    short opcode;
    short size;
    Instruction(string mnemonic, short opcode,short size){
        this->mnemonic = mnemonic;
        this->opcode = opcode;
        this->size =size;
    }

public:

    string getMnemonic(){
        return mnemonic;
    }

    short getOpcode(){
        return opcode;
    }

    short getSize(){
        return size;
    }
};

class Add: public Instruction{
public:
    string op;
    Add(string a): Instruction("ADD",1,2){
        op = a;
    }
};

class Sub: public Instruction{
public:    
    string op;
    Sub(string a): Instruction("SUB",2,2){
        op = a;
    }
};

class Mul: public Instruction{
public:
    string op;
    Mul(string a): Instruction("MUL",3,2){
        op = a;
    }
};

class Div: public Instruction{
public:
    string op;
    Div(string a): Instruction("DIV",4,2){
        op = a;
    }
};

class Jmp: public Instruction{
public:
    string op;
    Jmp(string a): Instruction("JMP",5,2){
        op = a;
    }
};

class Jmpn: public Instruction{
public:
    string op;
    Jmpn(string a): Instruction("JMPN",6,2){
        op = a;
    }
};

class Jmpp: public Instruction{
public:
    string op;
    Jmpp(string a): Instruction("JMPP",7,2){
        op = a;
    }
};

class Jmpz: public Instruction{
public:
    string op;
    Jmpz(string a): Instruction("JMPZ",8,2){
        op = a;
    }
};

class Copy: public Instruction{
public:
    string op1;
    string op2;
    Copy(string a,string b): Instruction("COPY",9,3){
        op1=a;
        op2=b;
    }
};
    

class Load: public Instruction{
public:
    string op;
    Load(string a): Instruction("LOAD",10,2){
        op=a;
    }
};
    
class Store: public Instruction{
public:
    string op;
    Store(string a): Instruction("STORE",11,2){
        op=a;
    }
};

class Input: public Instruction{
public:
    string op;
    Input(string a): Instruction("INPUT",12,2){
        op=a;
    }
};

class Output: public Instruction{
public:
    string op;
    Output(string a): Instruction("OUTPUT",13,2){
        op=a;
    }
};

class Stop: public Instruction{
public:
    Stop(): Instruction("STOP",14,1){}
};

ostream &operator<<(std::ostream &os, Instruction &a) { 
    return os <<a.getMnemonic()<<" ("<<a.getOpcode()<<") - sz: "<<a.getSize()<<"\n";
}



// Intruction getInstruction(vector<string> a){
//     string operation = a[0];
//     if (operation == "ADD") {
//         Intruction ans = Add add(a[1]);
//         return Instructiont
//     } else if (operation == "SUB") {
        
//     } else if (operation == "MUL") {
        
//     } else if (operation == "DIV") {
        
//     } else if (operation == "JMP") {
        
//     } else if (operation == "JMPN") {
        
//     } else if (operation == "JMPP") {
       
//     } else if (operation == "JMPZ") {
       
//     } else if (operation == "COPY") {
        
//     } else if (operation == "LOAD") {
        
//     } else if (operation == "STORE") {
        
//     } else if (operation == "INPUT") {
        
//     } else if (operation == "OUTPUT") {
        
//     } else if (operation == "STOP") {
        
//     } else {
//         std::cerr << "Error: Invalid operation!" << std::endl;
//     }

// }



Instruction* getInstruction(vector<string> a){
    string operation = a[0];
    if (operation == "ADD") {
        Add* ans = new Add(a[1]);
        return ans;
    } 
    if(operation == "COPY"){
        Copy* ans = new Copy(a[1],a[2]);
        return ans;
    }

}

