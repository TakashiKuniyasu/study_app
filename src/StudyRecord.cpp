#include <string>
#include <iostream>
#include <limits>
#include "StudyRecord.hpp"

void StudyRecord::input(int id){

    ID = id;

    std::cout << "学習内容を入力してください" << std::endl;
    std::cin >> content;

    std::cout << "日付を入力してください" << std::endl;
    std::cin >> date; 

    std::cout << "学習時間を入力してください" << std::endl;
    std::cin >> minute;
    while((std::cin.fail()) || (minute < 1)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "正しい学習時間を入力してください" << std::endl;
        std::cin >> minute;
    }
}

void StudyRecord::show() const{
    std::cout << "ID" << ID <<  "\n";    
    std::cout << "学習内容" << content <<  "\n";
    std::cout << "日付" << date << "\n";
    std::cout << "学習時間" << minute << "分\n"; 
}

int StudyRecord::getMinutes() const{
    return minute;
}

int StudyRecord::getID() const{
    return ID;
}

std::string StudyRecord::getDate() const{
    return date;
}

std::string StudyRecord::getContent() const{
    return content;
}
