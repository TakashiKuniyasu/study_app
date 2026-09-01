#include <iostream>
#include <string>
#include <limits>
#include "MainManager.hpp"

menu MainManager::userInput(){
    int num;
    menu menu_num;
    std::cout << "------------------------------" << std::endl;
    std::cout << "操作を選択してください" << std::endl;
    std::cout << "１．学習を記録する" << std::endl;
    std::cout << "２．学習記録を見る" << std::endl;
    std::cout << "３．学習記録を削除する" << std::endl;
    std::cout << "４．学習記録を検索する" << std::endl;
    std::cout << "５．学習記録を編集する" << std::endl;
    std::cout << "６．終了" << std::endl;

    std::cin >> num;
    while((std::cin.fail())||(num < 1 || num > 6)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "1〜6を入力してください" << std::endl;
        std::cin >> num;
    }
    menu_num = static_cast<menu>(num);
    return menu_num;
}
void MainManager::inputStudyRecord(std::string& content,
                      std::string& date,
                      int& minute){
    std::cout << "学習内容を入力してください" << std::endl;
    std::cin >> content;

    std::cout << "日付を入力してください" << std::endl;
    std::cin >> date; 

    std::cout << "学習時間を入力してください" << std::endl;
    std::cin >> minute;
}