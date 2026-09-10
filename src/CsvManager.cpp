#include <iostream>
#include <algorithm>
#include "CsvManager.hpp"
#include "StudyRecord.hpp"

bool CsvManager::csvIdCheck(const std::string& id,int& idNum){
    std::size_t pos;
    try{
        idNum = std::stoi(id, &pos);
        if(pos != id.size()){
            std::cout << "CSVのIDが不正です" << std::endl;
            return false;
        }
    }catch(...){
        std::cout << "CSVのIDが数値ではありません" << std::endl;
        return false;
    }
    return true;
}
bool CsvManager::csvMinutesCheck(const std::string& minutes, int& minutesNum){
    try{
        std::size_t pos;
        minutesNum = std::stoi(minutes, &pos);
        if(pos != minutes.size()){
            std::cout << "CSVの学習時間の値が数値ではありません" << std::endl;
            return false;
        }
        if(!StudyRecord::checkMinute(minutesNum)){
            return false;
        }
    }catch(...){
        std::cout << "CSVの学習時間が正しい数値ではありません" << std::endl;
        return false;;
    }
    return true;
}
bool CsvManager::parseCsvRecord(std::string& id,
                                std::string& content,
                                std::string& date,
                                std::string& minutes,
                                const std::string& line){
    std::stringstream ss(line);
    std::getline(ss,id,',');
    std::getline(ss,content,',');
    std::getline(ss,date,',');
    std::getline(ss,minutes,',');
    if(std::count(line.begin(), line.end(), ',') != 3){
            std::cout << "行の形式が不正です。" << std::endl;
            return false;
    }
    return true;
}