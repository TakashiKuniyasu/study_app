#include <iostream>
#include <cassert>
#include <filesystem>
#include "StudyManager.hpp"
#include "StudyManagerTest.hpp"

int main(){
    std::filesystem::remove("test_record.csv");

    addRecordTest();
    deleteRecordTest();
    editRecordTest();

    saveAndLoadRecordTest();

    std::error_code ec;
    if(std::filesystem::remove("test_record.csv",ec)){
        std::cout << "ファイル削除しました" << std::endl;
    }else{
        std::cout << "削除に失敗しました" << ec.message() << std::endl;
    }
}
void addRecordTest(){
    StudyManager manager("test_record.csv");
    std::string content = "C++";
    std::string date = "2026/8/28";
    int minute = 60;

    manager.addRecord(content, date, minute);
    assert(manager.getRecordCount() == 1);

    content = "Docker";
    date = "2026/8/29";
    minute = 80;

    manager.addRecord(content, date, minute);
    assert(manager.getRecordCount() == 2);
    return;
}
void deleteRecordTest(){
    std::filesystem::remove("test_record.csv");

    StudyManager manager("test_record.csv");

    manager.addRecord("C++", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/29", 80);

    manager.deleteRecord(2);

    assert(manager.getRecordCount() == 1);
    assert(manager.findRecordByID(1) != nullptr);
    assert(manager.findRecordByID(2) == nullptr);
}
void editRecordTest(){
    StudyManager manager("test_record.csv");
    std::string content = "C++";
    std::string date = "2026/8/28";
    int minute = 60;

    manager.addRecord(content, date, minute);
    manager.editPrevData(
        1,
        "CMake",
        "2026/8/31",
        75
    );
    const StudyRecord* record =
        manager.findRecordByID(1);
    
    assert(record != nullptr);
    assert(record->getID() == 1);
    assert(record->getContent() == "CMake");
    assert(record->getDate() == "2026/8/31");
    assert(record->getMinutes() == 75);
}
void saveAndLoadRecordTest(){
    StudyManager saveManager("test_record.csv");
    saveManager.addRecord("C++","2026/8/30",90);

    StudyManager loadManager("test_record.csv");
    loadManager.loadFromFile();
    assert(loadManager.getRecordCount() == 1);

    const StudyRecord* loadrecord =
        loadManager.findRecordByID(1);
    
    assert(loadrecord != nullptr);
    assert(loadrecord->getID() == 1);
    assert(loadrecord->getContent() == "C++");
    assert(loadrecord->getDate() ==  "2026/8/30");
    assert(loadrecord->getMinutes() == 90);

    loadManager.deleteRecord(2);
    assert(loadManager.getRecordCount() == 1);

    loadManager.editPrevData(
        2,
        "C++基礎",
        "2026/8/31",
        60
    );
    const StudyRecord* editTestRecord =
        loadManager.findRecordByID(1);
    
    assert(editTestRecord != nullptr);
    assert(editTestRecord->getID() == 1);
    assert(editTestRecord->getContent() == "C++");
    assert(editTestRecord->getDate() == "2026/8/30");
    assert(editTestRecord->getMinutes() == 90);

    loadManager.loadFromFile();
    assert(loadManager.getRecordCount() == 1);
    editTestRecord =
        loadManager.findRecordByID(1);
    assert(editTestRecord != nullptr);
    assert(editTestRecord->getID() == 1);
    assert(editTestRecord->getContent() == "C++");
    assert(editTestRecord->getDate() == "2026/8/30");
    assert(editTestRecord->getMinutes() == 90);
}