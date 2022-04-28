#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include <database.h>


typedef std::string str;
typedef std::tuple<str, str, int, int> loginTuple;
typedef std::ofstream out;
typedef std::ifstream in;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;

template<typename T>
str num_to_str(T num){
    char str[256] = "";
    std::snprintf(str, sizeof str, "%zu", num);
    return str;
}


str database::hash_str(str string){
    return num_to_str(hash_pass(string));
}

str database::get_input(str prompt){
    std::cout<<"Enter "<<prompt<<":"<<std::endl;
    str input;
    std::getline(std::cin, input);
    return input;
}

str database::random_password(){
    str password;
    for(int i=0; i<password_length; i++){
        int n = std::experimental::randint(0, int(password_chars.length())); //int?
        password+=password_chars[n];
    }
    return password;
}

void database::update_user_data(str login, str password="", str admin=""){
    data_vector data = read_database_to_vec();
    int index = get_user_index(login);
    str_vector user_vec = data[index];
    if(!password.empty()) user_vec[password_pos]=hash_str(password);
    if(!admin.empty()) user_vec[admin_pos] = admin;
    data[index] = user_vec;
    rewrite_database();
}

int database::get_user_index(str login){
    data_vector data = read_database_to_vec();
    for(int i=0; i<data.size(); i++){
        if(data[i][login_pos]==login){
            return i;
        }
    //throw !!!
    //return 0;
}


bool verify_password(str_vector vec, str input_password){
    return vec[1] == num_to_str(hash_pass(input_password));
}



str_vector get_user_data(str line){
    std::istringstream sline;
    str_vector vec;
    sline.str(line);
    for (str substr; std::getline(sline, substr, ','); ) {
        vec.push_back(substr);
    }
    return vec;
}


str_vector find_in_database(str login){
    data_vector data = read_database_to_vec();
    for(str_vector el:data){
        if(std::find(el.begin(), el.end(), login) != el.end()){
            return el;
        }
    }
    str_vector x = {"0"};   //throw
    return x;
}

bool already_in_database(str login){
    data_vector data = read_database_to_vec();
    for(str_vector el:data){
        if(std::find(el.begin(), el.end(), login) != el.end()){
            return true;
        }
    }
    return false;
    }



void log_in(str_vector data){
    if(std::stoi(data[2])){
        Admin user(data);
        check_password_change(user);
        admin_mode(user);
    }
    else{
        User user(data);
        check_password_change(user);
        user_mode(user);
    }
}