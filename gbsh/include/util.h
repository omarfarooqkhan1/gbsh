#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<vector>
std::string get_pwd();
std::string get_username();
std::string get_hostname();
void print_prompt();
void clear();
void trim_leading_whitespace(std::string& str);
void trim_trailing_whitespace(std::string& str);
void trim(std::string& str);
std::vector<std::string> tokenizer(const std::string& str, const char delimeter);
std::string resolve_path(std::string pwd, const std::string& args);
std::string get_homedir();
std::vector<std::string> get_envs();






#endif