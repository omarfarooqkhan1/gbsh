#include<iostream>
#include<string>
#include "util.h"
#include"commands.h"
#include<filesystem>
#include<unistd.h>
using namespace std;

template<typename T>
void consolePrint(const T& data){
    cout<<data<<'\n';
}


int main(int argc, char const *argv[]){
    
    const bool flag = true;
    string input;
    while(true && flag){
        cout<<"in llooop"<<endl;
        print_prompt();
        getline(cin,input);
        if(input.empty()) continue;
        trim(input);
        const vector<string> tokens = tokenizer(input,' ');
        const string& first = tokens[0];

        if(first == "exit"){
            break;
        }
        else if (first == "pwd"){
            consolePrint(get_pwd());
        }
        else if (first == "clear"){
            clear();
        }
        // else if (first == "ls"){
        //     ls(tokens);
        // }
        else if (first == "cd"){
            cd(tokens);
        }
        else if (first == "environ"){
            list_envs();
        }
        else if (first == "setenv"){
            set_env(tokens);
        }
        else if (first == "unsetenv"){
            unset_env(tokens);
        }
        else {
            transer_to_bash(tokens);
        }
    }    
    return 0;
}
