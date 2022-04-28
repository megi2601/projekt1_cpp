#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>

typedef std::string str;
typedef std::tuple<str, str, int, int> loginTuple;
typedef std::ofstream out;
typedef std::ifstream in;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;
std::hash<str> hash_pass;

class database
{
private:
    str filename;
    int login_pos = 0;
    int password_pos = 1;
    int admin_pos =2;
    int password_changes_pos = 3;
    str password_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int password_length = 8;
public:
    database(str filename){
        filename = filename;
    }
    str get_input(str);
    data_vector read_database_to_vec();
    int get_user_index(str);
    void update_user_data(str, str, str);
    void rewrite_database();
    str hash_str(str);
    str random_password();
    void rewrite_database(data_vector);
    str_vector return_user_data(str);
};