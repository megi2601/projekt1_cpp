#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include "modes.h"
#include <stdio.h>
#include <string.h>


typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;


void AdminMode::add_user(){
    str new_login = mode_database.get_input("new user's login");
    if(mode_database.is_in_database(new_login)){
        std::cout<<"Login already exists in database."<<std::endl;
        return;
    }
    str admin, reply;
    do{
        std::cout<<"Submit as a new admin? [Y/n]"<<std::endl;
        std::cin>>reply;
    }while(reply.compare("Y")!=0 && reply.compare("n")!=0);
    reply == "Y" ? admin="1" : admin = "0";
    str new_pass = mode_database.random_password();
    std::cout<<new_login<<"'s new password is:"<<std::endl
    <<new_pass<<std::endl<<"Remember to change it!"<<std::endl;
    mode_database.add_user(new_login, new_pass, admin);
}


void AdminMode::delete_user(){
    try{
        str login = mode_database.get_input("login to delete");
        mode_database.delete_user(login);
        std::cout<<"Done!\n";
    }
    catch(std::exception& e){
        std::cout<<e.what()<<"\n";
    }
}


void AdminMode::reset_password(){
    try{
        str user_login = mode_database.get_input("user's login");
        str new_pass = mode_database.random_password();
        mode_database.change_password(user_login, new_pass, true);
        std::cout<<user_login<<"'s new password is:"<<std::endl
        <<new_pass<<std::endl<<"Remember to change it!"<<std::endl;
    }
    catch(std::exception& e){
        std::cout<<e.what()<<"\n";
    }
}


void AdminMode::the_mode(){
    std::cout<<"WELCOME!\n";
    while(true){
        std::cout<<actions<<"Enter a number:\n";
        str input;
        std::cin>>input;
        int n_input;
        try{n_input = std::stoi(input);}
        catch(const std::invalid_argument&){n_input = 0;}
        switch (n_input)
        {
        case 1:
            read_file();
            break;
        case 2:
            change_password();
            break;
        case 3:
            add_user();
            break;
        case 4:
            delete_user();
            break;
        case 5:
            reset_password();
            break;
        case 6:
            std::cout<<"Goodbye!\n";
            return;
        default:
            std::cout<<"Wrong input.\n";
            break;
        }
    }
}