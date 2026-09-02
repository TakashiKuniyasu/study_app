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
            std::string content;
            std::string date;
            int minute;

            user.inputStudyRecord(content, date, minute);
            manager.addRecord(content, date, minute);
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
            int  id = user.inputID("削除したいIDを入力してください");
            manager.deleteRecord(id);
            break;
        }
        case menu::Search:
        {
            manager.searchContent();
            break;
        }
        case menu::Edit:
        {
            int id = user.inputID("編集したいIDを入力してください");

            std::string content;
            std::string date;
            int minute;

            user.inputStudyRecord(content, date, minute);

            manager.editPrevData(id, content, date, minute);
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