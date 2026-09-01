#include <iostream>
#include "StudyManager.hpp"
#include "MainManager.hpp"

int main(){
    MainManager user;
    StudyManager manager;
    manager.loadFromFile();

    while(true){

        menu menu_num = user.userInput();

        switch (menu_num)
        {
        case menu::Record:
        {
            manager.addRecord();
            break;
        }
        case menu::Watch:
        {
            manager.showRecords();
            manager.showTotalMinutes();   
            break;
        }
        case menu::Delete:
        {
            manager.deleteRecord();
            break;
        }
        case menu::Search:
        {
            manager.searchContent();
            break;
        }
        case menu::Edit:
        {
            manager.editPrevData();
            break;
        }
        case menu::Exit:
        {
            std::cout << "処理を終了します\n" << std::endl;
            return 0;
            break;
        }
        }
    }
    return 0;
}