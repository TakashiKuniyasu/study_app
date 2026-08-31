#include <iostream>
#include <limits>
#include "StudyRecord.hpp"
#include "StudyManager.hpp"

enum class menu{
    Record =1,
    Watch,
    Delete,
    Search,
    Exit
};

int main(){
    StudyManager manager;
    manager.loadFromFile();

    while(true){

        int num;
        std::cout << "------------------------------" << std::endl;
        std::cout << "操作を選択してください" << std::endl;
        std::cout << "１．学習を記録する" << std::endl;
        std::cout << "２．学習記録を見る" << std::endl;
        std::cout << "３．学習記録を削除する" << std::endl;
        std::cout << "４．学習記録を検索する" << std::endl;
        std::cout << "５．終了" << std::endl;

        std::cin >> num;
        while((std::cin.fail())||(num < 1 || num > 5)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "1〜5を入力してください" << std::endl;
            std::cin >> num;
        }
        menu menu_num;
        menu_num = static_cast<menu>(num);
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