#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
// using namespace std;
// hash<string> hash_pass;
typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;

// str database = "database.txt";

// str_vector get_user_data(str line){
//     std::istringstream sline;
//     str_vector vec;
//     sline.str(line);
//     for (str substr; std::getline(sline, substr, ','); ) {
//         vec.push_back(substr);
//     }
//     return vec;
// }

// data_vector read_database_to_vec(){
//     std::ifstream file_handle;
//     file_handle.open(database);
//     str line;
//     data_vector data;
//     while(std::getline(file_handle, line)){
//         data.push_back(get_user_data(line));
//     }
//     return data;
// }


int main(){
    str em = "";
    int n = std::size(em);
    std::cout<<n<<std::endl<<em.empty();
}