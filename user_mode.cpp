#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <experimental/random>
#include "modes.h"
// #include <database.h>



typedef std::string str;
typedef std::vector<str> str_vector;
typedef std::vector<str_vector> data_vector;


bool UserMode::change_password(){
    str new_pass = mode_database.get_input("your new password");
    bool changed = mode_database.change_password(login, new_pass);
    switch(changed)
    {case true:
        {user_data[mode_database.password_pos] = new_pass;
        str new_changes = mode_database.num_to_str(std::stoi(user_data[mode_database.password_changes_pos])+1);
        user_data[mode_database.password_changes_pos] = new_changes;
        std::cout<<"Password updated!"<<std::endl;
        return changed;}
    case false:
        std::cout<<"Password unchanged!"<<std::endl;
        return changed;
    }
}

void UserMode::check_password_change(){
    if(!std::stoi(user_data[mode_database.password_changes_pos])){
        bool changed;
        do{std::cout<<"You have to change the default password."<<std::endl;
        changed = change_password();}
        while(!changed);
    }
}

void UserMode::the_mode(){
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
            std::cout<<"Goodbye!\n";
            return;
        default:
            std::cout<<"Wrong input.\n";
            break;
        }
    }
}

void UserMode::read_file(){
    str filename =  mode_database.get_input("filename");
    mode_database.read_file(filename);
}


