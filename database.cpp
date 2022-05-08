#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include "database.h"
#include <stdio.h>
#include <string.h>
#include <exception>


typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;

class login_exception : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Login not found in the database.";
  }
} login_not_found;


class password_exception : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Wrong password.";
  }
} wrong_password;

template<typename T>
str Database::num_to_str(T num){
    char str[256] = "";
    std::snprintf(str, sizeof str, "%zu", num);
    return str;
}

data_vector Database::read_database_to_vec(){
    std::ifstream file_handle;
    file_handle.open(filename);
    str line;
    data_vector data;
    while(std::getline(file_handle, line)){
        data.push_back(read_user_line(line));
    }
    return data;
}

str Database::hash_str(str string){
    return num_to_str(hash_pass(string));
}


str Database::get_input(str prompt){
    std::cout<<"Enter "<<prompt<<":"<<std::endl;
    str input;
    std::cin>>input;
    return input;
}



str Database::random_password(){
    str password;
    for(int i=0; i<password_length; i++){
        int n = std::experimental::randint(0, int(password_chars.length())-1);
        password+=password_chars[n];
    }
    return password;
}

bool Database::is_in_database(str login){
    try{get_user_index(login); return true;}
    catch(login_exception&){return false;}
}



bool Database::change_password(str login, str new_pass, bool reset){
    data_vector data = read_database_to_vec();
    str_vector user_data = get_user_data(login);
    str hash = hash_str(new_pass);
    if(!new_pass.empty() && strcmp(user_data[password_pos].c_str(), hash.c_str())!=0){
        user_data[password_pos] = hash;
        if(reset){
            user_data[password_changes_pos] = "0";
        }
        else{
            str new_changes = num_to_str(std::stoi(user_data[password_changes_pos])+1);
            user_data[password_changes_pos] = new_changes;
        }
        data[get_user_index(login)] = user_data;
        rewrite_database(data);
        return true;
    }
    return false;
}


int Database::get_user_index(str login){
    data_vector data = read_database_to_vec();
    for(int i=0; i<data.size(); i++){
        if(data[i][login_pos]==login){
            return i;
        }
    }
    throw login_not_found;
}


void Database::add_user(str login, str password, str admin){
    data_vector data = read_database_to_vec();
    str hash = hash_str(password);
    str_vector user(records_num);
    user[login_pos] = login;
    user[password_pos] = hash;
    user[admin_pos] = admin;
    user[password_changes_pos] = "0";
    data.push_back(user);
    rewrite_database(data);
}

void Database::delete_user(str login){
    data_vector data = read_database_to_vec(), new_data;
    bool found = false;
    for(str_vector el:data){
        if(el[login_pos] != login){new_data.push_back(el);}
        else{found = true;}
    }
    if(!found){throw login_not_found;}
    rewrite_database(new_data);
}


str_vector Database::get_user_data(str login){
    data_vector data = read_database_to_vec();
    return data[get_user_index(login)];
}


bool Database::verify_password(str login, str pass){
    return get_user_data(login)[password_pos] == num_to_str(hash_pass(pass));
}

void Database::verify_login(str login, str password){
    str db_password = get_user_data(login)[password_pos];
    if(strcmp(db_password.c_str(), hash_str(password).c_str())!=0){
        throw wrong_password;
    }
}


str Database::vector_to_string(str_vector vec){
    str s;
    for(str el:vec) s+=el+",";
    return s;
}

void Database::rewrite_database(data_vector data){
    std::ofstream out;
    out.open(filename);
    for(str_vector el:data){
        str s = vector_to_string(el);
        out<<s<<"\n";
    }
    out.close();
}

str_vector Database::read_user_line(str line){
    std::istringstream sline;
    str_vector vec;
    sline.str(line);
    for (str substr; std::getline(sline, substr, ',');) {
        vec.push_back(substr);
    }
    return vec;
}


void Database::read_file(str filename){
    std::ifstream in;
    in.open(filename);
    if(!in.good()){
        std::cout<<"\nSomething wrong with the file, try again.\n"<<std::endl;
        return;
    }
    str line;
    std::cout<<"\n *** start *** \n";
    while(std::getline(in, line)){
        std::cout<<line<<std::endl;
    }
    std::cout<<"*** end *** \n";
}

bool Database::correct_database_file(){
    std::ifstream in(filename);
    return in.good();
}

void Database::create_database_file(){
    std::ofstream out;
    out.open(filename);
    out.close();
    std::cout<<"Create a database file. Enter login of the first admin:\n";
    str login;
    std::cin>>login;
    str password = random_password();
    std::cout<<login<<"'s new password is:\n"<<password<<"\n";
    add_user(login, password, "1");
}

bool Database::empty_file(){
    std::ifstream f;
    f.open(filename);
    return f.peek() == std::ifstream::traits_type::eof();
}