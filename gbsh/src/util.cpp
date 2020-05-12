#include"util.h"
#include<filesystem>
#include<string>
#include<unistd.h>
#include<vector>

using namespace std;

const string USERNAME = get_username();
const string HOSTNAME = get_hostname();

string get_pwd() {
    const auto path = filesystem::current_path();
    return string(path.c_str());
}

string get_username(){
    const size_t size = 256;
    char buffer[size];
    if( getlogin_r(buffer,size) == 0){
        return string(buffer);
    }
    return "";
}

string get_hostname(){
    const size_t size = 256;
    char buffer[size];
    if(gethostname(buffer,size) == 0){
        return string(buffer);
    }
    return "";
}

void print_prompt(){
    string path = get_pwd();
    const size_t loc = path.find(USERNAME);
    if (path.find("/home/"+USERNAME)!=string::npos)
        path = string("~") + path.substr(loc + USERNAME.length());
    cout<<USERNAME<<'@'<<HOSTNAME<<' '<<path<<" > ";
}

void clear(){
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    cout <<CLEAR_SCREEN_ANSI<<'\n';
}

vector<string> tokenizer(const string& str, const char delimeter){
    vector<string> tokens;
        string temp;
        temp.reserve(50);
        for (std::size_t i = 0, size = str.length(); i < size; i++){
            if (str[i] != delimeter)
            {
                temp += str[i];
            }
            else
            {
                if (!temp.empty())
                {
                    tokens.push_back(temp);
                    temp.clear();
                    temp.reserve(50);
                }
            }
        }
        if (!temp.empty())
            tokens.push_back(temp);
        return tokens;
}

void trim_leading_whitespace(string& str){
    auto end = str.end() -1;
    auto begin = str.begin();
    while(*end == ' ' &&  end!=begin){
        str.erase(end);
        --end;
        end = str.end() - 1;
    }
}

void trim_trailing_whitespace(string& str){
    auto end = str.end();
    auto begin = str.begin();
    while(*begin == ' ' && begin!=end){
        str.erase(begin);
        ++begin;
        begin = str.begin();
    }
}

void trim(string& str){
    trim_leading_whitespace(str);
    trim_trailing_whitespace(str);
}


string resolve_path(string pwd, const string& args){
    if (args =="/")
        return args;
    vector<string> tokens = tokenizer(args,'/');
    for(const auto& tok : tokens){
        if(tok == ".."){
            if(!pwd.empty())
                pwd = pwd.substr(0,pwd.find_last_of('/'));
        }
        else{
            pwd+='/';
            pwd+=tok;
        }
    }
    if(pwd.empty())
        pwd = "/";
    return pwd;
}  

std::string get_homedir(){
   return string("/home/")+USERNAME;
}

vector<string> get_envs(){
    vector<string> vars;
    char** var = environ;
    for(size_t i = 0; var[i]!=NULL; i++){
        vars.push_back(var[i]);
    }
    return vars;
}
