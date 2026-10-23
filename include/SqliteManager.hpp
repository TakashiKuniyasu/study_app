#pragma once
#include<sqlite3.h>
#include<string>
#include<vector>
#include<stdexcept>
#include "StudyRecord.hpp"

class SqliteManager{
public:
bool createTable();
bool insertRecord
    (const std::string&, 
     const std::string&, int);
bool deleteRecord(int);
bool updateRecord(int,
                const std::string&,
                const std::string&,
                int);
bool selectAllRecords(std::vector<StudyRecord>&);
bool selectRecords(std::vector<StudyRecord>&,
                    bool);
bool searchRecords(const std::string&, 
                std::vector<StudyRecord>&);

SqliteManager(const std::string& filename){
    if(!databaseOpen(filename)){
        throw std::runtime_error("DB接続失敗");
    }
}
~SqliteManager(){
    databaseClose();
}
SqliteManager(const SqliteManager&) = delete;
SqliteManager& operator=(const SqliteManager&) = delete;
private:
sqlite3* db = nullptr;
bool databaseOpen(const std::string&);
bool databaseClose();
};
