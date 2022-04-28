#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <database.h>

typedef std::string str;
typedef std::tuple<str, str, int, int> loginTuple;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;


class User {
    protected:
    str password;      //??????
    int admin;
    public:
    database mode_database;
    int password_changes;
    str login;
    User(str_vector data, database DB){
        mode_database=DB;
        login = data[0];
        password = data[1];  //hash za dlugi wtf
        admin = std::stoi(data[2]);
        password_changes = std::stoi(data[3]);
    };
    void change_password();

};


class Admin : public User{
    public:
    Admin(str_vector data, database DB) : User(data, DB){};
    void add_user_to_database(str alogin, str admin);
};