#include <bits/stdc++.h>
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

    // eliminates multiple spaces, EOL's and commentaries
    void cleanText(){
        string ans="";
        bool lastWasEOL=true;
        bool lastWasSpace=false;
        bool comment=false;
        bool firstAfterComment=false;
        
        for(char c: rawText){

            if(comment){
                if(c=='\n'){
                    comment=false;
                    firstAfterComment=true;
                }
                continue;
            }

            if(c==';'){
                comment=true;
                continue;
            }

            
            if(c==' '){
                if(!lastWasEOL && !lastWasSpace)ans+=c;
                lastWasSpace=true;
                lastWasEOL=false;
                continue;
            }

            if(c=='\n'){
                if(!lastWasEOL)ans+=c;
                lastWasEOL=true;
                lastWasSpace=false;
                continue;
            }

            if(firstAfterComment){
                ans+='\n';
                firstAfterComment=false;
            }

            ans+=c; 
            lastWasSpace=false;
            lastWasEOL=false;
            
        }
        rawText=ans;
    }

    string getRaw(){
        return rawText;
    }
    

};
int main(){
    InputFile input;
    input.readFile()->cleanText();
    cout<<input.getRaw();
}   