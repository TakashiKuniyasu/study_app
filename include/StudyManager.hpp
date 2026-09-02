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
    void loadFromFile(const std::string&);
    void searchContent(const std::string&);
    void editPrevData(int,
                      std::string&,
                      std::string&,
                      int&);
private:
    void saveToFile(const std::string&) const;
    int prevID=0;
};