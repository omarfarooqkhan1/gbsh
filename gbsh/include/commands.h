#ifndef COMMANDS_H
#define COMMANDS_H
#include<string>
#include<vector>

void ls(const std::vector<std::string>& tokens);
void cd(const std::vector<std::string>& tokens);
void list_envs();
void set_env(const std::vector<std::string>& tokens);
void unset_env(const std::vector<std::string>& tokens);
void transer_to_bash(const std::vector<std::string>& tokens);

#endif