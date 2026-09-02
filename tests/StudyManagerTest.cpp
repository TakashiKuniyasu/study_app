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
}