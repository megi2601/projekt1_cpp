#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include <exception>

typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;

class login_exception;


class password_exception;


class Database
{
public:
    str filename;
    int login_pos = 0;
    int password_pos = 1;
    int admin_pos =2;
    int password_changes_pos = 3;
    str password_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int password_length = 8;
    int records_num = 4;
    Database(str afilename){
        filename = afilename;
    }
    Database() = default;
    str get_input(str);
    data_vector read_database_to_vec();
    int get_user_index(str);
    str_vector read_user_line(str);
    bool change_password(str, str ="", bool=false);
    void rewrite_database();
    str hash_str(str);
    str random_password();
    void rewrite_database(data_vector);
    bool is_in_database(str);
    str vector_to_string(str_vector);
    void add_user(str, str, str);
    void delete_user(str);
    str_vector get_user_data(str);
    bool verify_password(str, str);
    void verify_login(str, str);
    void read_file(str);
    void create_database_file();
    bool correct_database_file();
    bool empty_file();
    template<typename T>
    str num_to_str(T);
};
