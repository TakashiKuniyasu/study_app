#pragma once
#include <vector>
#include "StudyRecord.hpp"

class StudyManager{
private:
    std::vector<StudyRecord> records;
public:
    void addRecord();
    void showRecords() const;
    void showTotalMinutes() const;
    void deleteRecord();
    void loadFromFile();
private:
    void saveToFile() const;
    int prevID=0;
};