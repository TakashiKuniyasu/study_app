#pragma once
#include <vector>
#include "StudyRecord.hpp"

class StudyManager{
private:
    std::vector<StudyRecord> records;
public:
    void addRecord(std::string&,
                    std::string&,
                    int&);
    void showRecords() const;
    void showTotalMinutes() const;
    void deleteRecord(int);
    void loadFromFile();
    void searchContent();
    void editPrevData(int,
                      std::string&,
                      std::string&,
                      int&);
private:
    void saveToFile() const;
    int prevID=0;
};