#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
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
void CsvManager::saveToFile(const std::string& fileName, 
                const std::vector<StudyRecord>& records){
    std::ofstream file(fileName);

    for(const auto& record : records){
        file << record.getID() << ",";
        file << record.getContent() << ",";
        file << record.getDate() << ",";
        file << record.getMinutes() << "\n";
    }
}
bool CsvManager::loadFromFile(const std::string& fileName, std::vector<StudyRecord>& records){
    std::ifstream file(fileName);

    if(!file){
        std::cout << "ファイルオープンエラー" << std::endl;
        return false;
    }
    int idNum;
    int minutesNum;
    std::string tmp;
    while(std::getline(file, tmp)){        
        std::string id;
        std::string content;
        std::string date;
        std::string minutes;

        if(!CsvManager::parseCsvRecord
            (id,content,date,minutes,tmp)){
            continue;
        }
        if(!CsvManager::csvIdCheck(id, idNum)){
            continue;
        }
        if(!StudyRecord::checkDate(date)){
            std::cout << "CSVの日付の値が適切ではありません" << std::endl;
            continue;
        }
        if(!CsvManager::csvMinutesCheck(minutes, minutesNum)){
            continue;
        }
        StudyRecord data(idNum,content,date,minutesNum);
        records.push_back(data);
    }
    return true;
}
