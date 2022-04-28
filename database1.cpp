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

template<typename T>
str num_to_str(T num){
    char str[256] = "";
    std::snprintf(str, sizeof str, "%zu", num);
    return str;
}


class User {
    protected:
    str password;      //??????
    int admin;
    public:
    int password_changes;
    str login;
    User(str_vector data){
        login = data[0];
        password = data[1];  //hash za dlugi wtf
        admin = std::stoi(data[2]);
        password_changes = std::stoi(data[3]);
    };
    void change_password();

};


class Admin : public User{
    public:
    Admin(str_vector data) : User(data){};
    void add_user_to_database(str alogin, str admin);
    str make_random_password();
};

str database = "database.txt";




bool verify_password(str_vector vec, str input_password){
    return vec[1] == num_to_str(hash_pass(input_password));
}


str get_input(str prompt){
    std::cout<<"Enter "<<prompt<<":"<<std::endl;
    str input;
    std::getline(std::cin, input);
    return input;
}

str vector_to_string(str_vector vec){
    str s;
    for(str el:vec) s+=el+",";
    return s;
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

data_vector read_database_to_vec(){
    in file_handle;
    file_handle.open(database);
    str line;
    data_vector data;
    while(std::getline(file_handle, line)){
        data.push_back(get_user_data(line));
    }
    return data;
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

void admin_mode(Admin&admin){
    std::cout<<"Welcome to the DaTaBaSe you ADMIN!"<<std::endl;
    adding_user(admin);
    while(true){str x;
    std::cin>>x;
    if (x=="clear")
    {
        system("cls");
    }
    }
}

void user_mode(User&){
    std::cout<<"Welcome to the DaTaBaSe"<<std::endl;
    while(true){str x;
    std::cin>>x;}
}



void overwrite_database(data_vector data){
    std::ofstream out;
    out.open(database);
    for(str_vector el:data){
        str s = vector_to_string(el);
        out<<s<<"\n";
    }
    out.close();
}

void User::change_password(){           // robić
    str new_pass;
    std::cout<<"Enter your new password below:"<<std::endl;
    std::cin>>new_pass;
    data_vector data = read_database_to_vec();
    for(int i=0; i<data.size(); i++){
        if(std::find(data[i].begin(), data[i].end(), login) != data[i].end()){
            str_vector user_vec = data[i];
            user_vec[1] = num_to_str(hash_pass(new_pass));
            user_vec[3] = num_to_str(std::stoi(user_vec[3])+1);
            data[i] = user_vec;
            break;   //settery nowych atrybutów
        }
    }
    overwrite_database(data);
}



// template<typename T>
// void request_password_change(str login){
//     str new_pass;
//     std::cout<<"Enter your new password below:"<<std::endl;
//     std::cin>>new_pass;
//     change_password(login, new_pass);
// }
template<typename T>
void check_password_change(T user){
    if(!user.password_changes){
        str request ="To use the database, you have to change the default password.";
        std::cout<<request<<std::endl;
        //request_password_change(user);
        user.change_password();
    }
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


str Admin::make_random_password(){
    int pass = std::experimental::randint(10000000, 9999999);
    str s_pass = num_to_str(pass);
    return s_pass;
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


int main(){
    str login = get_input("login");
    str password = get_input("password");
    str_vector data = find_in_database(login);
    while (!verify_password(data, password))
    {
        std::cout<<"Wrong password, try again!"<<std::endl;
        password = get_input("passwrord");
    }
    log_in(data);
    return 0;
    }