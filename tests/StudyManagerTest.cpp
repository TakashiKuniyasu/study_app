#include <iostream>
#include <cassert>
#include "StudyManager.hpp"

int main(){
    StudyManager test_manager("test_record.csv");
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

    test_manager.deleteRecord(2);
    assert(test_manager.getRecordCount() == 1);

    assert(test_manager.findRecordByID(1) != nullptr);
    assert(test_manager.findRecordByID(2) == nullptr);

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

    test_manager.deleteRecord(1);
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
    editTestRecord =
        loadManager.findRecordByID(1);
    assert(editTestRecord != nullptr);
    assert(editTestRecord->getID() == 1);
    assert(editTestRecord->getContent() == "C++");
    assert(editTestRecord->getDate() == "2026/8/30");
    assert(editTestRecord->getMinutes() == 90);
}