#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "StudyRecord.hpp"
#include "StudyManager.hpp"

StudyManager::StudyManager(const std::string& fileName)
    : fileName(fileName)
{}
void StudyManager::addRecord(const std::string& content,
                            const std::string& date,
                            int minute){
    prevID++;

    StudyRecord record(
        prevID,
        content,
        date,
        minute
    );

    records.push_back(record);
    saveToFile();
}
void StudyManager::showRecords() const{
   for(const StudyRecord& record : records){
        record.show();
    }
}
void StudyManager::deleteRecord(int num){

    for(auto it = records.begin(); it != records.end(); ++it){
        if(it->getID() == num){
            records.erase(it);
            saveToFile();
            return;
        }
    }
    std::cout << "削除できる内容がありません" << std::endl;
}
int StudyManager::getTotalMinutes() const{
    int total=0;

    for(const StudyRecord& record: records){
        total += record.getMinutes();
    }
    return total;
}
void StudyManager::showTotalMinutes() const{
    std::cout << "総学習時間" << getTotalMinutes() << "分\n";
}
void StudyManager::saveToFile() const{
    std::ofstream file(fileName);

    for(const auto& record : records){
        file << record.getID() << ",";
        file << record.getContent() << ",";
        file << record.getDate() << ",";
        file << record.getMinutes() << "\n";
    }
}
void StudyManager::loadFromFile(){

    std::ifstream file(fileName);
    if(!file){
        std::cout << "ファイルオープンエラー" << std::endl;
        return;
    }
    records.clear();
    prevID = 0;
    int idNum;
    int minutesNum;
    std::string tmp;
    while(std::getline(file, tmp)){
        std::stringstream ss(tmp);
        
        std::string id;
        std::string content;
        std::string date;
        std::string minutes;

        std::getline(ss,id,',');
        std::getline(ss,content,',');
        std::getline(ss,date,',');
        std::getline(ss,minutes,',');

        idNum = std::stoi(id);
        if(idNum > prevID){
            prevID = idNum;
        }
        try{
            minutesNum = std::stoi(minutes);
        }catch(...){
            std::cout << "CSVの学習時間が数値ではありません" << std::endl;
            return;
        }

        StudyRecord data(idNum,content,date,minutesNum);
        records.push_back(data);
    }
}
void StudyManager::searchContent(const std::string& word){
    bool found = false;
    for(const StudyRecord& record: records){
        if(record.getContent().find(word) != std::string::npos){
            record.show();
            found = true;
        }
    }
    if(found == false){
        std::cout << "学習内容が見つかりませんでした" << std::endl;
    }
}
void StudyManager::editPrevData(int id,
                                const std::string& content,
                                const std::string& date,
                                int minute){

    for(StudyRecord& record: records){
        if(id == record.getID()){
            record.update(content, date, minute);
            std::cout << "次のように編集しました" << std::endl;
            record.show();
            saveToFile();
            return;
        }
    }
    std::cout << "指定したIDが見つかりません" << std::endl;
    return;
}
std::size_t StudyManager::getRecordCount() const{
    return records.size();
}
const StudyRecord* StudyManager::findRecordByID(int id) const{
    for(const StudyRecord& record : records){
        if(record.getID() == id){
            return &record;
        }
    }
    return nullptr;
}
