#include <string>
#include <iostream>
#include <limits>
#include <ctime>
#include <sstream>
#include "StudyRecord.hpp"

void StudyRecord::input(int id){

    ID = id;
    std::cout << "学習内容を入力してください" << std::endl;
    std::cin >> content;

    std::cout << "日付を入力してください" << std::endl;
    std::cin >> date; 
    auto checkflg = checkDate(date);
    while(!checkflg){
        std::cout << "正しい日付を入力してください" << std::endl;
        std::cin >> date;        
        checkflg = checkDate(date);
    }

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

bool StudyRecord::checkDate(std::string date){
    std::stringstream ss(date);
    std::string sbuf;
    int ibuf;
    int day;
    int month;
    int year;
    
    // 年判定
    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }else{
        try{
            std::size_t pos;
            ibuf = stoi(sbuf, &pos);
            if(pos != sbuf.size()){
                std::cout << "入力が正しくありません" << std::endl; 
                return false;
            }
        }catch(...){
            std::cout << "入力が正しくありません" << std::endl;
            return false;
        }
        if((ibuf > 2026) || (ibuf < 2000)){
            return false;
        }else{
            year = ibuf;
        }
    }
    // 月判定
    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }
    else{
        try{
            std::size_t pos;
            ibuf = stoi(sbuf, &pos);
            if(pos != sbuf.size()){
                std::cout << "入力が正しくありません" << std::endl; 
                return false;
            }
        }catch(...){
            std::cout << "入力が正しくありません" << std::endl;
            return false;
        }
        if((ibuf < 1) || (ibuf > 12)){
            return false;
        }else{
            month = ibuf;
        }
    }
    // 日判定
    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }
    else{
        try{
            std::size_t pos;
            ibuf = stoi(sbuf, &pos);
            if(pos != sbuf.size()){
                std::cout << "入力が正しくありません" << std::endl; 
                return false;                
            }
        }catch(...){
            std::cout << "入力が正しくありません" << std::endl;
            return false;
        }
        if((ibuf < 1) || (ibuf > 31)){
            return false;
        }else{
            day = ibuf;
        }
    }
    if(!ss.eof()){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }
    return judgeExistDay(year, month, day);
}
bool StudyRecord::judgeExistDay(int year, int month, int day){

        Month m = static_cast<Month>(month);
        if(m == Month::February){
            if((year % 4 != 0) && (day == 29)){
                return false;
            }
        }

        if((m == Month::April) || 
           (m == Month::June) ||
           (m == Month::September) ||
           (m == Month::November)){
            if(day == 31){
                return false;
            }
           }
    return true;
}