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
}