#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "database.h"


typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;

// sprawdzić czy przydają się wszystkie atrybuty
class UserMode {
    protected:
    str admin;
    public:
    str_vector user_data;
    Database mode_database;
    str login;
    str actions = "\nHere's what you can do:\n1 - open a file\n2 - change your password\n3 - exit\n";
    UserMode(str_vector data, const Database& DB){
        user_data = data;
        mode_database=DB;
        login = data[mode_database.login_pos];
        admin = data[mode_database.admin_pos];
    };
    bool change_password();
    void check_password_change();
    void the_mode();
    void read_file();
};


class AdminMode : public UserMode{
    public:
    AdminMode(str_vector data, const Database& DB) : UserMode(data, DB){};
    str actions = "\nHere's what you can do:\n1 - open a file\n2 - change your password\n3 - add user\n4 - delete user\n5 - reset user's password\n6 - exit\n";
    void add_user();
    void delete_user();
    void reset_password();
    void the_mode();
};