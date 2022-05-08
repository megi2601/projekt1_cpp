#include "database.h"
#include "modes.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>


typedef std::string str;

str filename = "database.txt";
str help_mess = "This program logs you in the database.\nOptions:\n--help : help message\n--login <username> <password> : logs you in\nYou may ba asked to create the databse file (defaul name: database.txt).\n";


void log_in(str login, Database& db){
    str_vector data = db.get_user_data(login);
        if(std::stoi(data[db.admin_pos])){
            AdminMode user(data, db);
            user.check_password_change();
            user.the_mode();
        }
        else{
            UserMode user(data, db);
            user.check_password_change();
            user.the_mode();
        }
}


int main(int argc, char *argv[]){
    Database database(filename);
    if(!database.correct_database_file() || database.empty_file()){
        database.create_database_file();
        return 0;
    }
    str login, password;
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "--help")==0){
            std::cout<<help_mess;
            return 0;
        }
    }
    for(int i=0;i<argc-2;i++){
        if(strcmp(argv[i], "--login")==0){
            login = argv[i+1];
            password = argv[i+2];
        }
    }
    if(login.empty() || password.empty()){
        login = database.get_input("login");
        password = database.get_input("password");
    }
    while (true)
    {
        try{
            database.verify_login(login, password);
            log_in(login, database);
            break;
        }
        catch(std::exception& e){
            std::cout<<e.what()<<"\n";
            login = database.get_input("login");
            password = database.get_input("password");
        }
    }
}

