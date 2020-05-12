#include<iostream>
#include<string>
#include"util.h"
using namespace std;

template<typename T>
void consolePrint(const T& data){
    cout<<data<<'\n';
}


int main(int argc, char const *argv[]){

    string input;
    while(true){
        print_prompt();
        getline(cin,input);
        trim(input);
        const vector<string> tokens = tokenizer(input,' ');
        if(tokens.size() == 1){
            if(input == "exit"){
                break;
            }
            else if (input == "pwd"){
                consolePrint(get_pwd());
            }
            else if (input == "clear"){
                clear();
            }
            else if (input == "ls"){
                // list pwd stuff
            }
        }
        else{
            const string& first = tokens[0];
            if (first == "ls"){
                //cd into the directory and then ls
            }
        }
    }    
    return 0;
}
