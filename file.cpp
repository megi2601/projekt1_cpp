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

str vector_to_string(str_vector vec){
    str s;
    for(str el:vec) s+=el+",";
    return s;
}

void database::rewrite_database(data_vector data){
    std::ofstream out;
    out.open(filename);
    for(str_vector el:data){
        str s = vector_to_string(el);
        out<<s<<"\n";
    }
    out.close();
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

data_vector database::read_database_to_vec(){
    in file_handle;
    file_handle.open(filename);
    str line;
    data_vector data;
    while(std::getline(file_handle, line)){
        data.push_back(get_user_data(line));
    }
    return data;
}

str_vector database::return_user_data(str login){
    data_vector data = read_database_to_vec();
    return data[get_user_index(login)];
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

