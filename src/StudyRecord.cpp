#include <string>
#include <iostream>
#include <limits>
#include <ctime>
#include <sstream>
#include "StudyRecord.hpp"

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

bool StudyRecord::checkDate(const std::string& date){
    std::stringstream ss(date);
    int day;
    int month;
    int year;

    if(!checkDateYear(ss, year)){
        return false;
    }

    if(!checkDateMonth(ss, month)){
        return false;
    }

    if(!checkDateDay(ss, day)){
        return false;
    }

    return judgeExistDay(year, month, day);
}
bool StudyRecord::checkDateYear(std::stringstream& ss, int& year){
    int ibuf;
    std::string sbuf;
    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }else{
        if(!convertStringToInt(sbuf, ibuf)){
            return false;
        }
        if((ibuf > 2026) || (ibuf < 2000)){
            return false;
        }else{
            year = ibuf;
        }
    }
    return true;
}
bool StudyRecord::checkDateMonth(std::stringstream& ss, int& month){
    int ibuf;
    std::string sbuf;

    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }
    else{
        if(!convertStringToInt(sbuf, ibuf)){
            return false;
        }
        if((ibuf < 1) || (ibuf > 12)){
            return false;
        }else{
            month = ibuf;
        }
    }
    return true;
}
bool StudyRecord::checkDateDay(std::stringstream& ss, int& day){
    int ibuf;
    std::string sbuf;

    if(!getline(ss, sbuf, '/' )){
        std::cout << "入力が正しくありません" << std::endl;
        return false;
    }
    else{
        if(!convertStringToInt(sbuf, ibuf)){
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
    return true;
}
bool StudyRecord::convertStringToInt(std::string sbuf, int &ibuf){
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
    return true;
}
bool StudyRecord::judgeExistDay(int year, int month, int day){

        Month m = static_cast<Month>(month);
        if(m == Month::February){
            bool loopyear =
            ((year % 400 == 0) ||
            ((year % 4  == 0) && (year % 100 != 0)));

            if(loopyear){
                if(day > 29){
                    return false;
                }
            }else{
                if(day > 28){
                    return false;
                }
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
bool StudyRecord::checkMinute(int minute){
    return minute > 0;
}