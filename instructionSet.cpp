#include <bits/stdc++.h>
#define dbg(x) cout<<#x<<": "<<x<<"\n";
using namespace std;

class Instruction{
private:
    string mnemonic;
    short opcode;
    short size;
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

    vector<string> getArgs(){
        return args;
    }
};

// class UnknownOperand : public std::exception {
// private:
//     string message;

// public:
//     UnknownOperand(const string& operation) {
//         message = "Semantic Error! Operation " + operation + " is not part of the instruction set!";
//     }

//    const char* what() const noexcept override  {
//         return message.c_str();
//     }
// };

// class InvalidArgumentQtd : public exception {
// private:
//     string message;

// public:
//     InvalidArgumentQtd(const string& operation, int expected, int provided) {
//         message = "Semantic Error! Operation " + operation + " demands " +
//                   std::to_string(expected) + " arguments, whereas " +
//                   std::to_string(provided) + " were provided!";
//     }

//      const char* what() override {
//         return message.c_str();
//     }
// };

Instruction getInstruction(vector<string> a){
    string operation = a[0];

    if (operation == "ADD") {

       if(a.size()!=2){
            // throw InvalidArgumentQtd("ADD",1,a.size()-1);
       }
       a.erase(a.begin());
       return Instruction(operation,1,2,a);

    } else if (operation == "SUB") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("SUB",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,2,2,a);

    } else if (operation == "MUL") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("MUL",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,3,2,a);

    } else if (operation == "DIV") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("DIV",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,4,2,a);   
          
    } else if (operation == "JMP") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("JMP",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,5,2,a);   

    } else if (operation == "JMPN") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("JMPN",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,6,2,a);   

    } else if (operation == "JMPP") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("JMPP",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,7,2,a);   

    } else if (operation == "JMPZ") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("JMPZ",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,8,2,a);   

    } else if (operation == "COPY") {
        
        if(a.size()!=3){
            // throw InvalidArgumentQtd("COPY",2,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,9,3,a);   

    } else if (operation == "LOAD") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("LOAD",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,10,2,a);   

    } else if (operation == "STORE") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("STORE",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,11,2,a);  


    } else if (operation == "INPUT") {
        
        if(a.size()!=2){
            // throw InvalidArgumentQtd("INPUT",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,12,2,a);  
    
    } else if (operation == "OUTPUT") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("OUTPUT",1,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,13,2,a);  


    } else if (operation == "STOP") {

        if(a.size()!=2){
            // throw InvalidArgumentQtd("STOP",0,a.size()-1);
        }
        a.erase(a.begin());
        return Instruction(operation,14,1,a);  

    } else {
        // throw UnknownOperand(operation);
    }

}

ostream &operator<<(std::ostream &os, Instruction &a) { 
    string args="";
    for(auto c:a.getArgs())args+=(c+" ");
    return (os <<a.getMnemonic()<<" ("<<a.getOpcode()<<") - sz: "<<a.getSize()<<"\n"<<"args: "<<args<<"\n\n");

}


