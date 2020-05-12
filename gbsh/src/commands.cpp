#include"commands.h"
#include "util.h"
#include<filesystem>
#include<unistd.h>
#include<algorithm>
#include<stdlib.h>
#include<wait.h>
#include<string.h>
#include<memory>

static const int READ_END  = 0;
static const int WRITE_END = 1;

using namespace std;


void ls(const vector<string>& tokens){
    string path = get_pwd() ;
    if (tokens.size() > 2){
        cerr<<"Invalid arguments"<<endl;
        return;
    }
    if(tokens.size() > 1){
        path = resolve_path(get_pwd(),tokens[1]);
    }
    try{
        auto iterable = std::filesystem::directory_iterator(path);
        for (const auto entry : iterable){
            string tmp = entry.path().string();
            tmp = tmp.substr(tmp.find_last_of('/'));
            tmp.erase(tmp.begin());
            cout << tmp << endl;
        }
    }
    catch(const filesystem::__cxx11::filesystem_error& e){
        cerr<<"Invalid path: "<<path<<endl;
    }
}

void cd(const vector<string>& tokens){
    string path = get_pwd() ;
    if (tokens.size() > 2){
        cerr<<"Invalid arguments"<<endl;
        return;
    }
    if (tokens.size() == 1){
        path = get_homedir();
    }
    else if(tokens.size() > 1){
        path = resolve_path(get_pwd(),tokens[1]);
    }


    if(std::filesystem::exists(path))
        chdir(path.c_str());
    else
        cerr<<"Invalid Path"<<endl;
}

void list_envs(){
    vector<string> vars = get_envs();
    for(const auto& v : vars){
        cout<<v<<endl;
    }
}

void set_env(const vector<string>& tokens){
    vector<string> vars = get_envs();

    const auto& envar  = tokens[1];
    const auto& value  = tokens[2];
    auto flag = true;
    for (const auto& v : vars){
        if (v.find(envar)!=string::npos){
            flag = false;
            break;
        }
    }
    if (! flag){
        cerr <<envar <<" is already defined"<<endl;
        return;
    }
    setenv(envar.c_str(), value.c_str(),0);
}

void unset_env(const std::vector<std::string>& tokens){
    vector<string> vars = get_envs();
    const auto var = tokens[1];
    auto flag = false;
    for (const auto& v : vars){
        if (v.find(var)!=string::npos){
            flag = true;
            break;
        }
    }
    if (!flag){
        cerr <<var <<" is not defined"<<endl;
        return;
    }
    unsetenv(var.c_str());
}

void transer_to_bash(const vector<string>& tokens){
    string cmd;
    for(const auto& t : tokens){
        cmd+=t;
        cmd+=' ';
    }
    trim(cmd);
    const size_t size = tokens.size();
    char* args[size+1];
    int i = 0;
    for(const auto& t : tokens){
        args[i] = new char[t.length()+1];
        strcpy(args[i],t.c_str());
        ++i;
    }
    args[size] = NULL;
    int fd[2];
    int p = pipe(fd);
    if(p < 0) 
        cerr<<"error creating pipe"<<endl;
    if(!fork()){
        //this is child process
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO);  
        execv(tokens[0].c_str(),args);
    }
    close(fd[WRITE_END]);         // close the write end of the pipe
    char buffer[2048];
    size_t length = read(fd[READ_END], buffer, sizeof(buffer) - 1 );     //
    buffer[length] = '\0';
    cout<<buffer<<endl;
    for(int i = 0; i < size; i++){
        delete[] args[i];
    }
}