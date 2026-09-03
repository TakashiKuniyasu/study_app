#include <iostream>
#include <cassert>
#include <filesystem>
#include "StudyManager.hpp"
#include "StudyManagerTest.hpp"

int main(){
    std::filesystem::remove("test_record.csv");

    StudyManager test_manager("test_record.csv");

    addRecordTest(test_manager);
    deleteRecordTest(test_manager);
    editRecordTest(test_manager);
    test_manager.deleteRecord(1);
    saveAndLoadRecordTest();

    std::error_code ec;
    if(std::filesystem::remove("test_record.csv",ec)){
        std::cout << "ファイル削除しました" << std::endl;
    }else{
        std::cout << "削除に失敗しました" << ec.message() << std::endl;
    }
}
void addRecordTest(StudyManager& test_manager){
    std::string content = "C++";
    std::string date = "2026/8/28";
    int minute = 60;

    test_manager.addRecord(content, date, minute);
    assert(test_manager.getRecordCount() == 1);

    content = "Docker";
    date = "2026/8/29";
    minute = 80;

    test_manager.addRecord(content, date, minute);
    assert(test_manager.getRecordCount() == 2);
    return;
}
void deleteRecordTest(StudyManager& test_manager){
    test_manager.deleteRecord(2);
    assert(test_manager.getRecordCount() == 1);

    assert(test_manager.findRecordByID(1) != nullptr);
    assert(test_manager.findRecordByID(2) == nullptr);
}
void editRecordTest(StudyManager& test_manager){
    test_manager.editPrevData(
        1,
        "CMake",
        "2026/8/31",
        75
    );
    const StudyRecord* record =
        test_manager.findRecordByID(1);
    
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