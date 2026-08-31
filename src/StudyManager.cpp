#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "StudyRecord.hpp"
#include "StudyManager.hpp"

void StudyManager::addRecord(){
    StudyRecord record{0,"","",0};

    prevID++;

    record.input(prevID);
    records.push_back(record);

    saveToFile();
}
void StudyManager::showRecords() const{
   for(const StudyRecord& record : records){
        record.show();
    }
}
void StudyManager::deleteRecord(){
    int num;

    std::cout << "削除する内容を入力してください" << std::endl;
    std::cin >> num;

    for(auto it = records.begin(); it != records.end(); ++it){
        if(it->getID() == num){
            records.erase(it);
            saveToFile();
            return;
        }
    }
    std::cout << "削除できる内容がありません" << std::endl;
}

void StudyManager::showTotalMinutes() const{

    int total=0;

    for(const StudyRecord& record: records){
        total += record.getMinutes();
    }
    std::cout << "総学習時間" << total << "分\n";   
}
void StudyManager::saveToFile() const{
    std::ofstream file("study_records.csv");

    for(const auto& record : records){
        file << record.getID() << ",";
        file << record.getContent() << ",";
        file << record.getDate() << ",";
        file << record.getMinutes() << "\n";
    }
}
void StudyManager::loadFromFile(){

    std::ifstream file("study_records.csv");
    if(!file){
        std::cout << "ファイルオープンエラー" << std::endl;
        return;
    }
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
void StudyManager::searchContent(){
    std::string word;
    std::vector<StudyRecord> searchWordRecord;
    std::cout << "検索する学習内容を入力してください" << std::endl;
    std::cin >> word;
    for(const StudyRecord& record: records){
        if(record.getContent() == word){
            searchWordRecord.push_back(record);
        }
    }
    for(const StudyRecord& record : searchWordRecord){
        record.show();
    }
}