#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include <modes.h>


typedef std::string str;
typedef std::tuple<str, str, int, int> loginTuple;
typedef std::ofstream out;
typedef std::ifstream in;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;




void adding_user(Admin&admin){
    str new_login, reply, is_admin;
    std::cout<<"Enter new user's login:"<<std::endl;
    std::cin>>new_login;
    if(already_in_database(new_login)){
        std::cout<<"Login already exists in database."<<std::endl;
        return;
    }
    std::cout<<"Submit as a new admin? [Y/n]"<<std::endl;
    std::cin>>reply;
    reply == "Y" ? is_admin='1' : is_admin = '0';
    admin.add_user_to_database(new_login, is_admin);
}

void Admin::add_user_to_database(str alogin, str admin){
    data_vector data = read_database_to_vec();
    str new_pass = make_random_password();
    std::cout<<alogin<<"'s new password is:"<<std::endl
    <<new_pass<<std::endl<<"Remember to change it!"<<std::endl;
    str new_hash = num_to_str(hash_pass(new_pass));
    str_vector new_user = {alogin, new_hash, admin, "0"};
    data.push_back(new_user);
    overwrite_database(data);
    }

