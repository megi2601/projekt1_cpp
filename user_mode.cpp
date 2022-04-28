#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include <modes.h>
// #include <database.h>



typedef std::string str;
typedef std::tuple<str, str, int, int> loginTuple;
typedef std::ofstream out;
typedef std::ifstream in;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;


void User::change_password(){
    str new_pass = database.get_input("your new password");
    database.update_user_data(login, new_pass);
}


